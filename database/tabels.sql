DROP TABLE IF EXISTS incidents;
CREATE TABLE incidents(
    uuid            VARCHAR(32) NOT NULL UNIQUE,
    incident_type   VARCHAR(3) NOT NULL,
    timestamp       VARCHAR(60) NOT NULL,
    location        VARCHAR(20) NOT NULL,
    reporter_uuid   VARCHAR(32) NOT NULL
);

DROP TABLE IF EXISTS metrics;
CREATE TABLE metrics(
    uuid            VARCHAR(32) NOT NULL UNIQUE,
    user_uuid       VARCHAR(32) NOT NULL UNIQUE,
    speed           VARCHAR(32) NOT NULL,
    longitude       VARCHAR(32) NOT NULL,
    latitude        VARCHAR(32) NOT NULL
);

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

DROP TABLE IF EXISTS multimedia;
CREATE TABLE multimedia(
    uuid            VARCHAR(32) NOT NULL UNIQUE,
    timestamp        VARCHAR(60) NOT NULL,
    eventType        VARCHAR(128) NOT NULL,
    message        TEXT NOT NULL
);

DROP TABLE IF EXISTS sessions;
CREATE TABLE sessions(
    uuid                    VARCHAR(32) NOT NULL UNIQUE,
    user_uuid               VARCHAR(32) NOT NULL,
    identifier              VARCHAR(32) NOT NULL UNIQUE,
    validator               VARCHAR(32) NOT NULL UNIQUE,
    expiration_timestamp    VARCHAR(32) NOT NULL,
    creation_timestamp      VARCHAR(32) NOT NULL
);


INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("5e05ee71-3fc0-4dee-aa44-6c73ddb1634f", "1642014358", "1", "Tonight - Mostly clear. Winds NW at 7 to 9 mph (11.3 to 14.5 kph). The overnight low will be -5.6 C.");
INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("41793a5f-c72b-46bb-b3ac-6e486fd32c8a", "1642014458", "1", "Today - Mostly cloudy with a high of 1.1 C. Winds variable at 3 to 6 mph (4.8 to 9.7 kph).");
INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("e2fe59d3-f5c9-46ad-9db2-38902e9b63b2", "1642014458", "1", "Tomorrow - Cold with temperatures with highs of -3 C and lows of -9 C. Don't forget your snowman!");
INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("2453bbaf-4ff0-4f31-b4e6-5848c0329982", "1642014458", "1", "Tomorrow night - Cold again. Turn the climatronic to 24 degrees.");
INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("e7fd8ae4-7086-48cb-871f-0f37979a9d51", "1642014558", "2", "Price of fuel at PECO stations averages around 1,66 euro.");

INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("5d543445-807e-4592-a9ac-51e2f3a640cb", "1642014658", "2", "Price of fuel at ROMPETROM stations averages around 1.43 euro.");

INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("5298ce48-9656-4fd3-85c3-7681adfc336e", "1642014758", "2", "Price of fuel at OMV stations averages around 1.72 euro.");

INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("3c1d29c5-8faa-4e83-a224-484438abf4e9", "1642014858", "2", "Price of fuel at LUKOIL stations averages around 1.74 euro.");

INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("ead28a9d-9236-4d19-a795-f57cb0165951", "1642014958", "3", "World Poker Tour schedule 2022 Complete list of WPT event dates & how to watch Season 20");
INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("19d588ee-4b43-473d-bc7c-d6b41acca483", "1642015058", "3", "Ranking the NFL's open head coaching jobs, from best (Jaguars) to worst (Giants)");
INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("6f262712-0f27-4399-be9c-1de556324b81", "1642015158", "3", "Jameson Williams injury update - Alabama WR suffered torn ACL in national title game against Georgia");
INSERT INTO multimedia(uuid, timestamp, eventType, message)
VALUES ("09bd42ec-9dd5-44a8-b934-006b68a4af1f", "1642015258", "3", "Count on Nick Saban to use Georgia loss to push Alabama's dynasty forward next season");

INSERT INTO users(uuid, USERNAME, PASSWORD, EMAIL, FIRSTNAME, LASTNAME, COMPANY)
VALUES ("4e748142-3844-412e-9737-c068d0d5b667", "zaBogdan", "7a321f481f952fd8fb964ed1d2a5f86b4eaeecf5b6c04b73876dead6b780fd7e", "zabogdan@btruckers.org", "Bogdan", "Zavadovschi", "Wolveszone");

-- INSERT INTO users(uuid, USERNAME, PASSWORD, EMAIL, FIRSTNAME, LASTNAME, COMPANY)
-- VALUES ("6ca8222d-4a25-42f3-9f6a-6a0f6aa396cd", "gigi", "hashed", "gigi@devs.ro", "Gigi", "Camionagiul", "Gigi SRL");