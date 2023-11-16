-- insert part of columns 
INSERT INTO countries (country_id,country_name) VALUES('C1','India');

-- insert all columns
INSERT INTO countries  VALUES('C1','India', 003);

-- copy a table
create table A as B;
-- copy a table with data
create table A as select * from B;

-- insert multiple 
insert into Countries values("CN","ina",18),("ab","Cadadhasd",89);

-- update all column
UPDATE employees SET email='@google', commission_pct=0.10;

-- change table name
ALTER TABLE countries RENAME country_new;

-- add column
ALTER TABLE locations ADD region_id  INT;
-- add column as first column
ALTER TABLE locations ADD ID  INT FIRST;
-- add column after column
ALTER TABLE locations
ADD region_id INT 
AFTER state_province;

-- change column name with data
ALTER TABLE locations
CHANGE state_province state varchar(25);