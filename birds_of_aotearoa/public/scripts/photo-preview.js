
const fileInput = document.getElementById('photo');
const photoPreview = document.getElementById('photo-preview');
const photoContainer = document.getElementById('photo-container');
const inputs = document.getElementById('inputs');

const existingPhoto = photoPreview.getAttribute('src');

function showPreview() {
    photoContainer.style.display = 'flex';
    inputs.style.right = '55%';
    inputs.style.transform = 'translateX(0%)';
    inputs.style.maxWidth = '35%';
}

function hidePreview() {
    photoContainer.style.display = 'none';
    inputs.style.right = '50%';
    inputs.style.transform = 'translateX(50%)';
    inputs.style.maxWidth = '70%';
}

function change() {
    if (fileInput.files && fileInput.files[0]) {
        const reader = new FileReader();

        reader.onload = function (e) {
            photoPreview.src = e.target.result;
            showPreview();
        };

        reader.readAsDataURL(fileInput.files[0]);
    } else if (existingPhoto) {
        photoPreview.src = existingPhoto;
        showPreview();
    } else {
        photoPreview.removeAttribute('src');
        hidePreview();
    }
}

fileInput.addEventListener('change', change);
change();
