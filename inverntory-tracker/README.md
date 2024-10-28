# Inventory Management and Tracking System

This is a mini-project for a university **DBMS (Database Management System)** class. It is a web-based Inventory Management System that allows users to add, update, track, and delete products in an inventory. It features real-time product tracking, analytics for sold products with a visual pie chart, and a responsive user interface.

## Features

- **Add Products**: Enter product details such as name, price, profit, units sold, and units in stock.
- **View and Update Inventory**: View a list of products in the inventory with the option to update or delete items.
- **Sold Products Analytics**: A pie chart displays the proportion of each product sold.
- **Responsive Design**: A clean, user-friendly interface that adapts to different screen sizes.

## Project Structure

- **HTML**: The `index.html` file contains the structure of the inventory tracker UI.
- **CSS**: The `style.css` file styles the UI, including input fields, buttons, and cards for a dark-themed appearance.
- **JavaScript**: The `app.js` file provides client-side interactivity, including form handling, fetching data from the backend, updating the UI, and displaying the analytics chart.
- **Server**: The `server.js` file handles API endpoints for product data management, including adding, updating, deleting, and retrieving products.
- **Database**: MySQL is used for data persistence, storing all product-related information.

## Technologies Used

- **Frontend**: HTML, CSS, JavaScript, Chart.js (for pie chart analytics).
- **Backend**: Node.js with Express.js, MySQL database.
- **Additional Libraries**: CORS middleware for enabling cross-origin requests.

## Setup Instructions

### Prerequisites

- [Node.js](https://nodejs.org/) and npm installed
- [MySQL](https://www.mysql.com/) installed and running

### Step-by-Step Setup

1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd <repository-directory>

2. **Database Setup**
   - Open MySQL and execute the following commands to create the database and products table:
     ```sql
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
     ```

3. **Install Node.js Dependencies**
   - Install the required packages using npm:
     ```bash
     npm install express mysql cors
     ```

4. **Run the Server**
   - Start the backend server:
     ```bash
     node server.js
     ```
   - The server will be running at `http://localhost:3000`.

5. **Access the Application**
   - Open `index.html` in a browser or set up a local server to view the frontend.
   - Ensure `app.js` is correctly linked, and the backend API at `http://localhost:3000` is reachable.

## API Endpoints

- `POST /addProduct`: Add a new product to the inventory.
- `GET /products`: Retrieve a list of all products.
- `PUT /updateProduct`: Update the stock or sold count of a product.
- `DELETE /deleteProduct/:id`: Delete a product by its ID.
