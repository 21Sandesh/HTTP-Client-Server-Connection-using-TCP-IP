// Store the server's IP address in a variable
const serverIP = "192.168.1.7";

// Function to submit user data to the server
function submitData() {
  const name = document.getElementById("name").value;
  const prn = document.getElementById("prn").value;
  const division = document.getElementById("division").value;

  // Validate that Name, PRN, and Division are not empty
  if (name.trim() === "" || prn.trim() === "" || division.trim() === "") {
    alert("Please fill in all the required fields.");
    return;
  }

  const assignmentCheckboxes = document.querySelectorAll(
    'input[name="assignment"]:checked'
  );
  const assignments = Array.from(assignmentCheckboxes)
    .map((checkbox) => checkbox.value)
    .join(", ");

  const data = `\nName: ${name}\nPRN: ${prn}\nDivision: ${division}\nAssignments: ${assignments}`;

  fetch(`http://${serverIP}:8080`, {
    method: "POST",
    body: data,
  })
    .then((response) => response.text())
    .then((message) => {
      alert(message);
    })
    .catch((error) => console.error("Error:", error));
}

// Simple JavaScript code to fetch data from the server
fetch(`http://${serverIP}:8080`)
  .then((response) => response.text())
  .then((data) => {
    document.getElementById("activityData").textContent = data;

    // Parse the data and populate the table
    const entries = data.trim().split("\n\n");

    const tableBody = document.querySelector("#dataTable tbody");
    tableBody.innerHTML = ""; // Clear existing rows

    entries.forEach((entry) => {
      const rows = entry.split("\n");
      const newRow = tableBody.insertRow();

      rows.forEach((row) => {
        const [header, value] = row.split(": ");
        const cellElement = newRow.insertCell();
        cellElement.textContent = value;
      });

      // Add a line break after each entry
      tableBody.appendChild(document.createElement("br"));
    });
  })
  .catch((error) => console.error("Error:", error));