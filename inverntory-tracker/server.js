const express = require("express");
const mysql = require("mysql");
const cors = require("cors");
const app = express();
const port = 3000;

// MySQL Database connection
const db = mysql.createConnection({
  host: "localhost",
  user: "root", // XAMPP default MySQL username
  password: "", // XAMPP default MySQL password (empty by default)
  database: "inventory_db",
});

db.connect((err) => {
  if (err) throw err;
  console.log("Database connected...");
});

app.use(cors());
app.use(express.json());

// Add product
app.post("/addProduct", (req, res) => {
  const { name, price, profit, sold, inStock } = req.body;

  const query =
    "INSERT INTO products (name, price, profit, sold, in_stock) VALUES (?, ?, ?, ?, ?)";
  db.query(query, [name, price, profit, sold, inStock], (err, result) => {
    if (err) {
      console.error("Error adding product:", err);
      return res.status(500).send(err);
    }
    res.send({ message: "Product added successfully!" });
  });
});

// Update product stock/sold
app.put("/updateProduct", (req, res) => {
  const { id, sold, inStock } = req.body;

  db.query(
    "UPDATE products SET sold = ?, in_stock = ? WHERE id = ?",
    [sold, inStock, id],
    (error, results) => {
      if (error) {
        console.error("Error updating product:", error);
        return res.status(500).send(error);
      }
      res.send({ message: "Product updated successfully" });
    }
  );
});

// Delete product
app.delete("/deleteProduct/:id", (req, res) => {
  const { id } = req.params;

  db.query("DELETE FROM products WHERE id = ?", [id], (error, results) => {
    if (error) {
      console.error("Error deleting product:", error);
      return res.status(500).send(error);
    }

    if (results.affectedRows === 0) {
      return res.status(404).send({ message: "Product not found" });
    }

    res.send({ message: "Product deleted successfully" });
  });
});

// Get all products
app.get("/products", (req, res) => {
  db.query("SELECT * FROM products", (err, results) => {
    if (err) {
      console.error("Error fetching products:", err);
      return res.status(500).send(err);
    }
    res.json(results);
  });
});

app.listen(port, () => {
  console.log(`Server running on http://localhost:${port}`);
});
