const express = require('express');
const path = require('path');
const pool = require('./db');
const birds_router = require('./birds_router');
router = express.Router();
const db = pool.promise();

router.use(express.urlencoded({ extended: true }));
router.use('/', express.static(path.resolve(__dirname, 'public')));
router.use('/birds/', birds_router);

router.get('/', async (req, res) => {
    res.redirect('/birds')
});

router.get('/birds', async (req, res) => {
    const query = `SELECT Bird.*, ConservationStatus.status_name, ConservationStatus.status_colour, Photos.filename, Photos.photographer 
    FROM Bird LEFT JOIN ConservationStatus ON Bird.status_id = ConservationStatus.status_id LEFT JOIN Photos ON Bird.bird_id = Photos.bird_id
    ORDER BY Bird.primary_name ASC;`
    const status_query = `SELECT * FROM ConservationStatus;`;

    const [rows, fields] = await db.query(query);
    const [status_rows, status_fields] = await db.query(status_query);
    
    res.render('index', { title: 'Birds of Aotearoa', birds: rows, status: status_rows});
});

router.get('/filter', async (req, res) => {
    let statusString = "";

    console.log(req.query);
    if(!(req.query['All-status'] === 'on')){
        for(const param in req.query){
            if(req.query[param] === 'on'){
                statusString = (statusString === "" ? statusString.concat(`WHERE (ConservationStatus.status_name = '${param}'`) : statusString.concat(` OR ConservationStatus.status_name = '${param}'`));
            }
        }
    }

    let sizeString = '';
    let sizeStringPartial = getSize(req.query['size']);
    if(req.query['All-status'] === 'on'){
        sizeString = (req.query['size'] === "All" ? '' : `WHERE ${sizeStringPartial}`);
    }
    else{
        sizeString = (req.query['size'] === "All" ? '' : `) AND ${sizeStringPartial}`);
    }

    let sortString = (req.query['All-status'] != 'on' && req.query['size'] === "All" ? ') ORDER BY ' + sort(req.query['sort']) : 'ORDER BY ' + sort(req.query['sort']));    

    const query = `SELECT Bird.*, ConservationStatus.status_name, ConservationStatus.status_colour, Photos.filename, Photos.photographer 
    FROM Bird LEFT JOIN ConservationStatus ON Bird.status_id = ConservationStatus.status_id LEFT JOIN Photos ON Bird.bird_id = Photos.bird_id
    ${statusString || ''}${sizeString || ''} ${sortString || ''};`
    const status_query = `SELECT * FROM ConservationStatus;`;


    const [rows, fields] = await db.query(query, statusString);
    const [status_rows, status_fields] = await db.query(status_query);
    
    res.render('index', { title: 'Birds of Aotearoa', birds: rows, status: status_rows});
});

function getSize(size){
    if(size === "Small"){
        return 'Bird.length <= 20';
    }
    else if(size === "Medium"){
        return 'Bird.length > 20 AND Bird.length <= 40';
    }
    else if(size === "Large"){
        return 'Bird.length > 40';
    }
    else{
        return '';
    }
}

function sort(sortElement){
    switch(sortElement){
        case "M\u0101ori name":
            return "Bird.primary_name";
        case "English Name":
            return "Bird.english_name";
        case "Scientific Name":
            return "Bird.scientific_name";
        case "Photographer":
            return "Photos.photographer";
        case "Family":
            return "Bird.family";
        case "Order":
            return "Bird.order_name";
        case "Conservation Status":
            return "ConservationStatus.status_id";
        case "Lightest to Heaviest":
            return "CAST(Bird.weight AS DECIMAL)";
        case "Heaviest to Lightest":
            return "CAST(Bird.weight AS DECIMAL) DESC";
        case "Shortest to Longest":
            return "CAST(Bird.length AS DECIMAL)";
        case "Longest to Shortest":
            return "CAST(Bird.length AS DECIMAL) DESC";
    }
    return "";
}

router.get('/search', async(req, res) => {
    const searchTerm = String(req.query.search ?? '').trim().normalize('NFC');
    const query = `SELECT Bird.*, ConservationStatus.status_name, ConservationStatus.status_colour, Photos.filename, Photos.photographer 
    FROM Bird LEFT JOIN ConservationStatus ON Bird.status_id = ConservationStatus.status_id LEFT JOIN Photos ON Bird.bird_id = Photos.bird_id
    WHERE Bird.english_name LIKE '${searchTerm}%' OR Bird.primary_name LIKE '${searchTerm}%' OR Bird.scientific_name LIKE '${searchTerm}%'
    OR Bird.family LIKE '${searchTerm}%' OR Bird.order_name LIKE '${searchTerm}%' ORDER BY Bird.primary_name ASC;`
    const status_query = `SELECT * FROM ConservationStatus;`;

    const [rows, fields] = await db.query(query, searchTerm);
    const [status_rows, status_fields] = await db.query(status_query);
    
    res.render('index', { title: 'Birds of Aotearoa', birds: rows, status: status_rows});
});

router.get('*', async (req, res) => {
    res.status(404)
    res.render('404');
});

module.exports = router;