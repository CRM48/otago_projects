# Birds of Aotearoa

A web application for exploring and managing information about native New Zealand birds. Developed for COSC203 at the University of Otago (2023).

The application starts with 68 bird records and lets users search, filter, sort, view, add, edit and delete birds. Each record includes names, taxonomy, conservation status, size and a photograph with credit.

## Features

- Browse birds and open individual information pages.
- Search by Māori, English or scientific name, family or order.
- Filter by conservation status and size, and sort using different attributes.
- Create and edit bird records, including uploading or replacing photographs.
- Delete birds and clean up uploaded photographs that are no longer used

## Technologies

Node.js, Express, EJS, MySQL, Docker, HTML, CSS, JavaScript and Multer (for image uploads).

## Requirements

- Node.js and npm
- Docker Desktop (or Docker Engine with Docker Compose)
- Git Bash on Windows for the SQL import commands below (or a shell that supports `<` input redirection)

## Setup and run

Run all commands from the `birds_of_aotearoa` folder.

**1. Start MySQL**

```bash
docker compose up -d
```

The container is called `cosc203mysql`. MySQL is available on port **3307** on the host machine (port **3306** inside Docker). Wait until MySQL has finished starting before importing the data.

**2. Initialise the database (first run only)**

```bash
docker exec -i cosc203mysql mysql --default-character-set=utf8mb4 -uroot -ppassword < sql/db_setup.sql
docker exec -i cosc203mysql mysql --default-character-set=utf8mb4 -uroot -ppassword ASGN2 < sql/db_populate.sql
```

These scripts create the database tables and load the original bird records. UTF-8 is specified explicitly to preserve Māori macrons. The password-on-command-line warning is expected for this local setup.

**Important:** `db_setup.sql` drops and recreates `ASGN2`. Do **not** rerun it unless you want to reset the database and lose changes made in the application.

**3. Install dependencies**

```bash
npm ci
```

**4. Start the application**

```bash
npm start
```

Visit **http://localhost:3000** in your browser.

## Using the application

On the homepage, browse the bird list or use the search bar, filters and sorting controls to find birds. Select a bird to view its full details. Use the create option to add a bird with a photograph; on a bird's details page, use **Edit** to update its information or optionally replace its photo, or **Delete** to remove it.

Uploaded photographs are saved in `public/images/`. Replaced or deleted uploads are removed when they are no longer referenced. The original dataset images remain in the project.

## Stopping and restarting

Stop the Node.js server with `Ctrl+C`. Stop the database container with:

```bash
docker compose down
```

To use the application again, run `docker compose up -d`, followed by `npm start`. The database data is retained between normal stops and restarts; there is no need to reimport it.

To check the database record count:

```bash
docker exec cosc203mysql mysql -ucosc203 -ppassword ASGN2 -e "SELECT COUNT(*) AS birds FROM Bird;"
```

The original dataset contains **68 birds**.

## Project structure

```text
birds_of_aotearoa/
├── public/                 # CSS, client-side scripts, icons and bird images
├── sql/                    # Database schema and initial data
│   ├── db_setup.sql
│   └── db_populate.sql
├── views/                  # EJS pages and reusable partials
├── server.js               # Express server
├── path_router.js          # Listing, search, filtering and sorting
├── birds_router.js         # Bird details and create/edit/delete routes
├── db.js                   # MySQL connection
├── docker-compose.yml      # MySQL container configuration
├── package.json
└── package-lock.json
```

## Notes

This is a local university coursework project, not a production-deployed service. The included database credentials are for the local Docker setup only. The application has no user authentication and should not be exposed publicly without additional security work.

Generated files such as `node_modules/` and `mysql-data/` should not be committed to Git.