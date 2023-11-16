select * from customers


-- create when not exist 

CREATE TABLE IF NOT EXISTS countries ( 
COUNTRY_ID varchar(2),
COUNTRY_NAME varchar(40),
REGION_ID decimal(10,0)
);

-- copy a table
CREATE TABLE IF NOT EXISTS dup_countries
LIKE countries;

-- copy a table with data
CREATE TABLE IF NOT EXISTS dup_countries
AS SELECT * FROM  countries;


-- view table schema
DESC dup_countries;

-- null value
CREATE TABLE IF NOT EXISTS countries ( 
COUNTRY_ID varchar(2) NOT NULL,
COUNTRY_NAME varchar(40) NOT NULL,
REGION_ID decimal(10,0) NOT NULL
);

-- field check
CREATE TABLE IF NOT EXISTS jobs ( 
JOB_ID varchar(10) NOT NULL , 
JOB_TITLE varchar(35) NOT NULL, 
MIN_SALARY decimal(6,0), 
MAX_SALARY decimal(6,0) 
CHECK(MAX_SALARY<=25000)
);


CREATE TABLE IF NOT EXISTS countries ( 
COUNTRY_ID varchar(2),
COUNTRY_NAME varchar(40)
CHECK(COUNTRY_NAME IN('Italy','India','China')) ,
REGION_ID decimal(10,0),
UNIQUE(COUNTRY_ID)
);
 -- UNIQUE PRIMARY KEY,
CREATE TABLE IF NOT EXISTS jobs ( 
JOB_ID varchar(10) NOT NULL UNIQUE, 
JOB_TITLE varchar(35) NOT NULL DEFAULT ' ', 
MIN_SALARY decimal(6,0) DEFAULT 8000, 
MAX_SALARY decimal(6,0) DEFAULT NULL
);

CREATE TABLE IF NOT EXISTS countries (
COUNTRY_ID varchar(2) NOT NULL UNIQUE DEFAULT '',
COUNTRY_NAME varchar(40) DEFAULT NULL,
REGION_ID decimal(10,0) NOT NULL,
PRIMARY KEY (COUNTRY_ID,REGION_ID));


CREATE TABLE IF NOT EXISTS employees ( 
EMPLOYEE_ID decimal(6,0) NOT NULL PRIMARY KEY, 
FIRST_NAME varchar(20) DEFAULT NULL, 
LAST_NAME varchar(25) NOT NULL, 
JOB_ID INTEGER, 
SALARY decimal(8,2) DEFAULT NULL, 
FOREIGN KEY(JOB_ID) 
REFERENCES  jobs(JOB_ID)
ON DELETE SET NULL 
ON UPDATE SET NULL
) ENGINE=InnoDB;
