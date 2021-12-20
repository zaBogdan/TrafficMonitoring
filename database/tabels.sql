DROP TABLE IF EXISTS users;
CREATE TABLE users(
    uuid            VARCHAR(32) NOT NULL,
    username        VARCHAR(60) NOT NULL,
    password        VARCHAR(128) NOT NULL,
    email        VARCHAR(128) NOT NULL,
    firstname        VARCHAR(128),
    lastname        VARCHAR(128),
    company        VARCHAR(128) 
);

INSERT INTO users(uuid, USERNAME, PASSWORD, EMAIL, FIRSTNAME, LASTNAME, COMPANY)
VALUES ("4e748142-3844-412e-9737-c068d0d5b667", "zaBogdan", "hashed", "zabogdan@btruckers.org", "Bogdan", "Zavadovschi", "Wolveszone");

INSERT INTO users(uuid, USERNAME, PASSWORD, EMAIL, FIRSTNAME, LASTNAME, COMPANY)
VALUES ("6ca8222d-4a25-42f3-9f6a-6a0f6aa396cd", "gigi", "hashed", "gigi@devs.ro", "Gigi", "Camionagiul", "Gigi SRL");