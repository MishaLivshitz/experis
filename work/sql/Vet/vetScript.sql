--  Sample employee database 
--  See changelog table for details
--  Copyright (C) 2007,2008, MySQL AB
--  
--  Original data created by Fusheng Wang and Carlo Zaniolo
--  http://www.cs.aau.dk/TimeCenter/software.htm
--  http://www.cs.aau.dk/TimeCenter/Data/employeeTemporalDataSet.zip
-- 
--  Current schema by Giuseppe Maxia 
--  Data conversion from XML to relational by Patrick Crews
-- 
-- This work is licensed under the 
-- Creative Commons Attribution-Share Alike 3.0 Unported License. 
-- To view a copy of this license, visit 
-- http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to 
-- Creative Commons, 171 Second Street, Suite 300, San Francisco, 
-- California, 94105, USA.
-- 
--  DISCLAIMER
--  To the best of our knowledge, this data is fabricated, and
--  it does not correspond to real people. 
--  Any similarity to existing people is purely coincidental.
-- 

DROP DATABASE IF EXISTS vet;
CREATE DATABASE IF NOT EXISTS vet;
USE vet;

SELECT 'CREATING DATABASE STRUCTURE' as 'INFO';

DROP TABLE IF EXISTS costumers,
                     pets;

/*!50503 set default_storage_engine = InnoDB */;
/*!50503 select CONCAT('storage engine: ', @@default_storage_engine) as INFO */;

CREATE TABLE costumers (
    costumer_no      INT             	NOT NULL,
    c_name  VARCHAR(25)     			NOT NULL,
    PRIMARY KEY (costumer_no)
);

CREATE TABLE pets (
    pet_no     		CHAR(4)         NOT NULL,
	costumer_no		INT				NOT NULL,
    p_name  		VARCHAR(40)     NOT NULL,
    PRIMARY KEY (pet_no),
  	FOREIGN KEY (costumer_no) REFERENCES costumers (costumer_no) ON DELETE CASCADE
);

INSERT INTO costumers(costumer_no, c_name) VALUES(1,"Misha"), (2, "Mar1");

INSERT INTO pets(pet_no, costumer_no, p_name) VALUES(1,1, "Drogo"), (2, 2, "Dario");

