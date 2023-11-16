DROP TABLE IF EXISTS regions;
CREATE TABLE regions (
 REGION_ID decimal(5,0) NOT NULL PRIMARY KEY,
  REGION_NAME varchar(25) DEFAULT NULL
);


DROP TABLE IF EXISTS countries;
CREATE TABLE countries     (
  COUNTRY_ID varchar(2) NOT NULL,
  COUNTRY_NAME varchar(40) DEFAULT NULL,
  REGION_ID decimal(10,0) DEFAULT NULL,
  PRIMARY KEY (COUNTRY_ID),
  KEY COUNTR_REG_FK (REGION_ID)
) ;


DROP TABLE IF EXISTS locations;
CREATE TABLE locations (
  LOCATION_ID decimal(4,0) NOT NULL DEFAULT 0,
  STREET_ADDRESS varchar(40) DEFAULT NULL,
  POSTAL_CODE varchar(12) DEFAULT NULL,
  CITY varchar(30) NOT NULL,
  STATE_PROVINCE varchar(25) DEFAULT NULL,
  COUNTRY_ID varchar(2) DEFAULT NULL,
  PRIMARY KEY (LOCATION_ID),
  KEY LOC_CITY_IX (CITY),
  KEY LOC_COUNTRY_IX (COUNTRY_ID),
  KEY LOC_STATE_PROVINCE_IX (STATE_PROVINCE)
);


DROP TABLE IF EXISTS jobs;
CREATE TABLE jobs (
  JOB_ID varchar(10) NOT NULL DEFAULT '',
  JOB_TITLE varchar(35) NOT NULL,
  MIN_SALARY decimal(6,0) DEFAULT NULL,
  MAX_SALARY decimal(6,0) DEFAULT NULL,
  PRIMARY KEY (JOB_ID)
) ;


DROP TABLE IF EXISTS job_history;
CREATE TABLE job_history (
  EMPLOYEE_ID decimal(6,0) NOT NULL,
  START_DATE date NOT NULL,
  END_DATE date NOT NULL,
  JOB_ID varchar(10) NOT NULL,
  DEPARTMENT_ID decimal(4,0) DEFAULT NULL,
  PRIMARY KEY (EMPLOYEE_ID,START_DATE),
  KEY JHIST_DEPARTMENT_IX (DEPARTMENT_ID),
  KEY JHIST_EMPLOYEE_IX (EMPLOYEE_ID),
  KEY JHIST_JOB_IX (JOB_ID)
);


DROP TABLE IF EXISTS departments;
CREATE TABLE departments (
  DEPARTMENT_ID decimal(4,0) NOT NULL DEFAULT '0',
  DEPARTMENT_NAME varchar(30) NOT NULL,
  MANAGER_ID decimal(6,0) DEFAULT NULL,
  LOCATION_ID decimal(4,0) DEFAULT NULL,
  PRIMARY KEY (DEPARTMENT_ID),
  KEY DEPT_MGR_FK (MANAGER_ID),
  KEY DEPT_LOCATION_IX (LOCATION_ID)
);

DROP TABLE IF EXISTS employees;
CREATE TABLE employees (
 EMPLOYEE_ID decimal(6,0) NOT NULL DEFAULT '0',
 FIRST_NAME varchar(20) DEFAULT NULL,
 LAST_NAME varchar(25) NOT NULL,
 EMAIL varchar(25) NOT NULL,
 PHONE_NUMBER varchar(20) DEFAULT NULL,
 HIRE_DATE date NOT NULL,
 JOB_ID varchar(10) NOT NULL,
 SALARY decimal(8,2) DEFAULT NULL,
 COMMISSION_PCT decimal(2,2) DEFAULT NULL,
 MANAGER_ID decimal(6,0) DEFAULT NULL,
 DEPARTMENT_ID decimal(4,0) DEFAULT NULL,
 PRIMARY KEY (EMPLOYEE_ID),
 KEY EMP_DEPARTMENT_IX (DEPARTMENT_ID),
 KEY EMP_JOB_IX (JOB_ID),
 KEY EMP_MANAGER_IX (MANAGER_ID),
 KEY EMP_NAME_IX (LAST_NAME,FIRST_NAME)
);


INSERT INTO regions VALUES (1,'Europe\r'),(2,'Americas\r'),(3,'Asia\r'),(4,'Middle East and Africa\r');

INSERT INTO countries VALUES ('AR','Argentina',2),
('AU','Australia',3),
('BE','Belgium',1),
('BR','Brazil',2),
('CA','Canada',2),
('CH','Switzerland',1),
('CN','China',3),
('DE','Germany',1),
('DK','Denmark',1),
('EG','Egypt',4),
('FR','France',1),
('HK','HongKong',3),
('IL','Israel',4),
('IN','India',3),
('IT','Italy',1),
('JP','Japan',3),
('KW','Kuwait',4),
('MX','Mexico',2),
('NG','Nigeria',4),
('NL','Netherlands',1),
('SG','Singapore',3),
('UK','United Kingdom',1),
('US','United States of America',2),
('ZM','Zambia',4),('ZW','Zimbabwe',4);


INSERT INTO locations VALUES (1000,'1297 Via Cola di Rie','989','Roma','','IT'),
(1100,'93091 Calle della Testa','10934','Venice','','IT'),
(1200,'2017 Shinjuku-ku','1689','Tokyo','Tokyo Prefecture','JP'),
(1300,'9450 Kamiya-cho','6823','Hiroshima','','JP'),
(1400,'2014 Jabberwocky Rd','26192','Southlake','Texas','US'),
(1500,'2011 Interiors Blvd','99236','South San Francisco','California','US'),
(1600,'2007 Zagora St','50090','South Brunswick','New Jersey','US'),
(1700,'2004 Charade Rd','98199','Seattle','Washington','US'),
(1800,'147 Spadina Ave','M5V 2L7','Toronto','Ontario','CA'),
(1900,'6092 Boxwood St','YSW 9T2','Whitehorse','Yukon','CA'),
(2000,'40-5-12 Laogianggen','190518','Beijing','','CN'),
(2100,'1298 Vileparle (E)','490231','Bombay','Maharashtra','IN'),
(2200,'12-98 Victoria Street','2901','Sydney','New South Wales','AU'),
(2300,'198 Clementi North','540198','Singapore','','SG'),
(2400,'8204 Arthur St','','London','','UK'),
(2500,'Magdalen Centre',' The Oxford ','OX9 9ZB','Oxford','Ox'),
(2600,'9702 Chester Road','9629850293','Stretford','Manchester','UK'),
(2700,'Schwanthalerstr. 7031','80925','Munich','Bavaria','DE'),
(2800,'Rua Frei Caneca 1360','01307-002','Sao Paulo','Sao Paulo','BR'),
(2900,'20 Rue des Corps-Saints','1730','Geneva','Geneve','CH'),
(3000,'Murtenstrasse 921','3095','Bern','BE','CH'),
(3100,'Pieter Breughelstraat 837','3029SK','Utrecht','Utrecht','NL'),
(3200,'Mariano Escobedo 9991','11932','Mexico City','\"Distrito Federal','\"');

INSERT INTO jobs VALUES ('AD_PRES','President',20000,40000),
('AD_VP','Administration Vice President',15000,30000),
('AD_ASST','Administration Assistant',3000,6000),
('FI_MGR','Finance Manager',8200,16000),
('FI_ACCOUNT','Accountant',4200,9000),
('AC_MGR','Accounting Manager',8200,16000),
('AC_ACCOUNT','Public Accountant',4200,9000),
('SA_MAN','Sales Manager',10000,20000),
('SA_REP','Sales Representative',6000,12000),
('PU_MAN','Purchasing Manager',8000,15000),
('PU_CLERK','Purchasing Clerk',2500,5500),
('ST_MAN','Stock Manager',5500,8500),
('ST_CLERK','Stock Clerk',2000,5000),
('SH_CLERK','Shipping Clerk',2500,5500),
('IT_PROG','Programmer',4000,10000),
('MK_MAN','Marketing Manager',9000,15000),
('MK_REP','Marketing Representative',4000,9000),
('HR_REP','Human Resources Representative',4000,9000),
('PR_REP','Public Relations Representative',4500,10500);

INSERT INTO job_history VALUES (102,'1993-01-13','1998-07-24','IT_PROG',60),
(101,'1989-09-21','1993-10-27','AC_ACCOUNT',110),
(101,'1993-10-28','1997-03-15','AC_MGR',110),
(201,'1996-02-17','1999-12-19','MK_REP',20),
(114,'1998-03-24','1999-12-31','ST_CLERK',50),
(122,'1999-01-01','1999-12-31','ST_CLERK',50),
(200,'1987-09-17','1993-06-17','AD_ASST',90),
(176,'1998-03-24','1998-12-31','SA_REP',80),
(176,'1999-01-01','1999-12-31','SA_MAN',80),
(200,'1994-07-01','1998-12-31','AC_ACCOUNT',90),
(0,'0000-00-00','0000-00-00','',0);

INSERT INTO departments VALUES (10,'Administration',200,1700),
(20,'Marketing',201,1800),(30,'Purchasing',114,1700),
(40,'Human Resources',203,2400),(50,'Shipping',121,1500),
(60,'IT',103,1400),(70,'Public Relations',204,2700),
(80,'Sales',145,2500),(90,'Executive',100,1700),
(100,'Finance',108,1700),(110,'Accounting',205,1700),
(120,'Treasury',0,1700),(130,'Corporate Tax',0,1700),
(140,'Control And Credit',0,1700),(150,'Shareholder Services',0,1700),
(160,'Benefits',0,1700),(170,'Manufacturing',0,1700),
(180,'Construction',0,1700),(190,'Contracting',0,1700),
(200,'Operations',0,1700),(210,'IT Support',0,1700),
(220,'NOC',0,1700),(230,'IT Helpdesk',0,1700),
(240,'Government Sales',0,1700),(250,'Retail Sales',0,1700),
(260,'Recruiting',0,1700),(270,'Payroll',0,1700);

INSERT INTO employees VALUES (100,'Steven','King','SKING','515.123.4567','1987-06-17','AD_PRES',24000.00,0.00,0,90),
(101,'Neena','Kochhar','NKOCHHAR','515.123.4568','1987-06-18','AD_VP',17000.00,0.00,100,90),
(102,'Lex','De Haan','LDEHAAN','515.123.4569','1987-06-19','AD_VP',17000.00,0.00,100,90),
(103,'Alexander','Hunold','AHUNOLD','590.423.4567','1987-06-20','IT_PROG',9000.00,0.00,102,60),
(104,'Bruce','Ernst','BERNST','590.423.4568','1987-06-21','IT_PROG',6000.00,0.00,103,60);


SELECT * FROM employees;
UPDATE employees SET email='not available';


select * from employees;