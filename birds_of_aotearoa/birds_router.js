const express = require('express'); // import express
const path = require('path');
const pool = require('./db');
const router = express.Router(); // create a router
const db = pool.promise();
const multer = require('multer');
const fs = require('fs/promises');
let file_name;

//allows for unique file name with date function
//Sets destination for file uploads as public/images/
const storage = multer.diskStorage(
    {
        destination: (req, file, cb) => {
            cb(null, path.join(__dirname, 'public', 'images'));
        },
        filename: function (req, file, cb){
            file_name = Date.now() + '-' + file.originalname;
            cb(null, file_name);
        }
    }
);

const upload = multer( { storage: storage } );

async function removeUploadedPhoto(filename) {
    // Only remove uploaded files, not the original bird images
    if (!/^\d{13}-[^/\\]+$/.test(filename || '')) {
        return;
    }

    // Check whether another bird still references the image
    const [rows] = await db.query(
        'SELECT COUNT(*) AS count FROM Photos WHERE filename = ?',
        [filename]
    );

    if (rows[0].count > 0) {
        return;
    }

    const filePath = path.join(__dirname, 'public', 'images', filename);

    try {
        await fs.unlink(filePath);
    } catch (err) {
        if (err.code !== 'ENOENT') {
            console.error('Failed to remove photograph:', err);
        }
    }
}

router.use(express.urlencoded({ extended: true }));

router.get('/create', async (req, res) => {
    const status = `SELECT * FROM ConservationStatus;`;
    [status_rows, status_fields] = await db.query(status);
    res.render('create', {status: status_rows});
});

router.get('/:id', async (req, res) => {
    let bird_checked = null;
    const query = `SELECT Bird.*, ConservationStatus.status_name, ConservationStatus.status_colour, Photos.filename, Photos.photographer 
    FROM Bird LEFT JOIN ConservationStatus ON Bird.status_id = ConservationStatus.status_id LEFT JOIN Photos ON Bird.bird_id = Photos.bird_id; `
    

    const [rows, fields] = await db.query(query);
    const id = req.params.id;
    for(const bird of rows){
        if(bird.bird_id == id){
            bird_checked = bird;
        }
    }
    if(bird_checked == null){
        res.status(404);
        res.render('404');
    }
    else{
        res.render('information', { bird: bird_checked });
    }
    
});

router.get('/:id/update', async (req, res) => {
    const id = req.params.id;
    let bird_checked;
    const query = `SELECT Bird.*, ConservationStatus.status_name, ConservationStatus.status_colour, Photos.filename, Photos.photographer 
    FROM Bird LEFT JOIN ConservationStatus ON Bird.status_id = ConservationStatus.status_id LEFT JOIN Photos ON Bird.bird_id = Photos.bird_id; `;
    const status = `SELECT * FROM ConservationStatus;`;

    const [rows, fields] = await db.query(query);
    for(const bird of rows){
        if(bird.bird_id == id){
            bird_checked = bird;
        }
    }
    [status_rows, status_fields] = await db.query(status);
    if(bird_checked == null){
        res.status(404);
        res.render('404');
    }
    else{
        res.render('update', { status: status_rows, bird: bird_checked });
    }
});


router.post('/:id/delete', async (req, res) => {
    const id = req.params.id;
    const [birds] = await db.query('SELECT bird_id FROM Bird WHERE bird_id = ?', [id]);

    if (birds.length === 0) {
        return res.status(404).render('404');
    }

    const [photos] = await db.query('SELECT filename FROM Photos WHERE bird_id = ?', [id]);
    await db.query('DELETE FROM Photos WHERE bird_id = ?', [id]);
    await db.query('DELETE FROM Bird WHERE bird_id = ?', [id]);

    for (const photo of photos) {
        await removeUploadedPhoto(photo.filename);
    }

    res.redirect('/');
});







router.post('/create', upload.single('photo'), async (req, res) => {
    const birds = `SELECT * FROM Bird;`;
    [bird_rows, bird_fields] = await db.query(birds);
    const status = `SELECT * FROM ConservationStatus;`;
    [status_rows, status_fields] = await db.query(status);
    const bid = findBirdID(bird_rows);
    const sid = findStatusID(status_rows, req.body.conservation_status);
    const eName = req.body.english_name;
    const pName = req.body.primary_name;
    const sName = req.body.scientific_name;
    const oName = req.body.order_name;
    const fName = req.body.family;
    const bird_weight = req.body.weight;
    const bird_length = req.body.length;
    const photo_credit = req.body.credit;
    const photoName = file_name;
    
    const create_bird = 'INSERT INTO Bird (bird_id, primary_name, english_name, scientific_name, order_name, family, weight, length, status_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);';
    const create_photo = 'INSERT INTO Photos (bird_id, filename, photographer) VALUES (?, ?, ?);';
    [b_rows, b_fields] = await db.query(create_bird, [bid, pName, eName, sName, oName, fName, bird_weight, bird_length, sid]);
    [s_rows, s_fields] = await db.query(create_photo, [bid, photoName, photo_credit]);
    res.redirect('/')
});

function findBirdID(birds){
    const ids = new Set()
    for(const bird of birds){
        ids.add(bird.bird_id);
    }
    for(let i = 1; i <= birds.length; i++){
        if(!ids.has(i)){
            return i;
        }
    }
    return birds.length+1;
}

function findStatusID(status_array, status_name){
    for(let i = 0; i < status_array.length; i++){
        if(status_name == status_array[i].status_name){
            return status_array[i].status_id;
        }
    }
    return "error";
}


router.post('/edit', upload.single('photo'), async (req, res) => {
    const status = `SELECT * FROM ConservationStatus;`;
    [status_rows, status_fields] = await db.query(status);
    const bid = req.body.bird_id;
    const sid = findStatusID(status_rows, req.body.conservation_status);
    const eName = req.body.english_name;
    const pName = req.body.primary_name;
    const sName = req.body.scientific_name;
    const oName = req.body.order_name;
    const fName = req.body.family;
    const bird_weight = req.body.weight;
    const bird_length = req.body.length;
    const photo_credit = req.body.credit;
    const photo = req.file ? req.file.filename : null;

    let oldPhoto = null;

    if (photo) {
        const [rows] = await db.query('SELECT filename FROM Photos WHERE bird_id = ? LIMIT 1', [bid]);
        oldPhoto = rows[0]?.filename;
    }
    
    const update_bird = `UPDATE Bird SET primary_name = ?, english_name = ?, scientific_name = ?, order_name = ?, family = ?, weight = ?, length = ?, status_id = ? WHERE bird_id = ?;`;
    await db.query(update_bird, [pName, eName, sName, oName, fName, bird_weight, bird_length, sid, bid]);

    if (photo) {
        await db.query('UPDATE Photos SET filename = ?, photographer = ? WHERE bird_id = ?;', [photo, photo_credit, bid]);
    } 
    else {
        await db.query('UPDATE Photos SET photographer = ? WHERE bird_id = ?;', [photo_credit, bid]);
    } 

    if (photo && oldPhoto && oldPhoto !== photo) {
        await removeUploadedPhoto(oldPhoto);
    }
    res.redirect('/')
});

module.exports = router;