document
  .getElementById("productForm")
  .addEventListener("submit", async function (e) {
    e.preventDefault();

    const productData = {
      name: document.getElementById("name").value,
      price: parseFloat(document.getElementById("price").value),
      profit: parseFloat(document.getElementById("profit").value),
      sold: parseInt(document.getElementById("sold").value),
      inStock: parseInt(document.getElementById("inStock").value),
    };

    try {
      const response = await fetch("http://localhost:3000/addProduct", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(productData),
      });

      if (!response.ok) {
        throw new Error("Failed to add product");
      }

      // Clear the input fields
      document.getElementById("productForm").reset();
      loadProducts(); // Reload products after adding a new one
    } catch (error) {
      console.error("Error adding product:", error);
    }
  });

async function loadProducts() {
  try {
    const response = await fetch("http://localhost:3000/products");

    if (!response.ok) {
      throw new Error("Network response was not ok");
    }

    const products = await response.json();
    console.log("Fetched products:", products);

    const productList = document.getElementById("productList");
    productList.innerHTML = ""; // Clear list before reloading

    // Call renderProduct for each product
    products.forEach((product) => {
      renderProduct(product); // Use the renderProduct function
    });

    // Call the function to render the pie chart
    renderSoldProductsChart(); // Render pie chart after loading products
  } catch (error) {
    console.error("Error loading products:", error);
  }
}

// Function to render a single product as a card
function renderProduct(product) {
  const productCard = document.createElement("div");
  productCard.className = "product-card";

  productCard.innerHTML = `
    <p><strong>Name:</strong> ${product.name}</p>
    <p><strong>Price:</strong> ₹${product.price}</p>
    <p><strong>Profit:</strong> ₹${product.profit}</p>
    <p><strong>Sold:</strong> ${product.sold}</p>
    <p><strong>In Stock:</strong> ${product.in_stock}</p>
    <input type="number" id="sold-${product.id}" value="${product.sold}" placeholder="Update Sold">
    <input type="number" id="inStock-${product.id}" value="${product.in_stock}" placeholder="Update In Stock">
    <div>
      <button onclick="updateProduct(${product.id})">Update</button>
      <button onclick="deleteProduct(${product.id})" class="button delete-button">Delete</button>
    </div>
  `;

  document.getElementById("productList").appendChild(productCard);
}

async function updateProduct(id) {
  const sold = document.getElementById(`sold-${id}`).value;
  const inStock = document.getElementById(`inStock-${id}`).value;

  await fetch("http://localhost:3000/updateProduct", {
    method: "PUT",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ id, sold, inStock }),
  });

  loadProducts(); // Reload products after updating
}

// New function to delete a product
async function deleteProduct(id) {
  try {
    const response = await fetch(`http://localhost:3000/deleteProduct/${id}`, {
      method: "DELETE",
    });

    if (!response.ok) {
      throw new Error("Failed to delete product");
    }

    loadProducts(); // Reload products after deleting
  } catch (error) {
    console.error("Error deleting product:", error);
  }
}

// Render Pie Chart showing sold products
async function renderSoldProductsChart() {
  try {
    const response = await fetch("http://localhost:3000/products");
    const products = await response.json();

    const soldData = products.map((product) => product.sold);
    const productLabels = products.map((product) => product.name);

    const ctx = document.getElementById("soldProductsChart").getContext("2d");
    const soldProductsChart = new Chart(ctx, {
      type: "pie",
      data: {
        labels: productLabels,
        datasets: [
          {
            data: soldData,
            backgroundColor: [
              "#FF6384",
              "#36A2EB",
              "#FFCE56",
              "#4BC0C0",
              "#9966FF",
              "#FF9F40",
            ],
          },
        ],
      },
      options: {
        responsive: true,
        plugins: {
          legend: {
            position: "top",
          },
          title: {
            display: true,
            text: "Products Sold",
          },
        },
      },
    });
  } catch (error) {
    console.error("Error rendering chart:", error);
  }
}

// Load products on initial page load
loadProducts();
