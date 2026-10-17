-- Recreate the application database
DROP DATABASE IF EXISTS ASGN2;
CREATE DATABASE ASGN2
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE ASGN2;

-- create tables
CREATE TABLE ConservationStatus (
    status_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    status_name VARCHAR(255) NOT NULL,
    status_colour CHAR(7) NOT NULL
);

CREATE TABLE Bird (
    bird_id INT NOT NULL PRIMARY KEY,
    english_name VARCHAR(255) NOT NULL,
    primary_name VARCHAR(255) NOT NULL,
    scientific_name VARCHAR(255) NOT NULL,
    order_name VARCHAR(255) NOT NULL,
    family VARCHAR(255) NOT NULL,
    length VARCHAR(25) NOT NULL,
    weight VARCHAR(25) NOT NULL,
    status_id INT NOT NULL,
    FOREIGN KEY (status_id) REFERENCES ConservationStatus(status_id)
);

CREATE TABLE Photos (
    photo_id INT NOT NULL DEFAULT 1,
    filename VARCHAR(255) NOT NULL,
    photographer VARCHAR(50) NOT NULL,
    bird_id INT NOT NULL,
    PRIMARY KEY(photo_id, bird_id),
    FOREIGN KEY (bird_id) REFERENCES Bird(bird_id)
);


