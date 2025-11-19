# 📒 Address Book Management System (C Programming)

A command-line Address Book application built using C. This project enables users to add, search, edit, delete, list, save, and load contacts with persistent storage. The program follows a modular, multi-file structure for better clarity and maintainability.

---

## 🚀 Features

### ✔ Create Contact
- Add new contacts with **name**, **10-digit phone number**, and **email**
- Input validation:
  - Only digits allowed for phone number
  - Must be exactly 10 digits
  - Unique phone number and email
  - Email must contain `@` and `.com`

### ✔ Search Contact
- Search by **name**, **number**, or **email**
- Partial case-insensitive name search
- Displays all matching contacts

### ✔ Edit Contact
- Modify **name**, **number**, or **email**
- Full validation and duplicate checks applied

### ✔ Delete Contact
- Delete contact by name, phone, or email
- Supports multiple matches (user selects which one)
- Shifts contact list after deletion

### ✔ List Contacts
- Displays all contacts in a formatted table

### ✔ File Persistence
- Saves contacts to `contacts.txt`
- Auto-loads saved contacts during program start
- Format:
        count,name,phone,email
---

## 📂 Project Structure

├── main.c `# Application menu & program flow`

├── contact.c `# Create, search, edit, delete, list`

├── file.c `# Load & save contacts to file`

├── populate.c `# Optional dummy data for testing`

├── contact.h `# Structs & function prototypes`

├── file.h

├── populate.h

└── contacts.txt `# Auto-generated persistent storage file`

---

## 🛠 Technologies Used

- **C Language**
- Structures & arrays
- File handling (`fopen`, `fscanf`, `fprintf`)
- Modular programming
- String manipulation (`strcasestr`, `strcmp`, etc.)

---

## ▶️ How to Compile & Run

### Compile:
```
gcc main.c contact.c file.c populate.c -o addressbook
./addressbook

```
📸 Sample Menu Output
```
----Address Book Menu----
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
Enter your choice:
```
---
📌 Future Enhancements
A–Z alphabetical sorting

Export to CSV/JSON

Unlimited dynamic memory support

ncurses-based text UI

Backup & restore features

