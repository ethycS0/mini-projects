CREATE DATABASE inventory_db;

USE inventory_db;

CREATE TABLE products (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(255) NOT NULL,
  price DECIMAL(10, 2) NOT NULL,
  profit DECIMAL(10, 2) NOT NULL,
  sold INT NOT NULL,
  in_stock INT NOT NULL
);


npm install express mysql cors

http://localhost/phpmyadmin/
http://localhost:3000