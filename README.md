# ATM Simulation Project

## Overview
This project is a simple ATM simulation system developed in C++. It allows users to perform basic banking operations such as checking their account balance, withdrawing money, depositing money, viewing transaction history, and creating new accounts. The data for user accounts and transactions is stored in a text file (`atm.txt`).

## Features
- **Withdraw money**: Users can withdraw funds from their accounts.
- **Deposit money**: Users can deposit funds into their accounts.
- **Check balance**: Displays the current balance of the user.
- **View transaction history**: Shows the last 5 transactions of the user.
- **Account creation**: Allows users to create new accounts with an initial balance.
- **Secure login**: Passwords are hidden during input for security.

## Tech Stack
- **Language**: C++
- **File Handling**: Data is stored in a text file (`atm.txt`) and updated after each transaction.
- **Libraries**:
  - `<iostream>` for input/output.
  - `<fstream>` for file handling.
  - `<vector>` for dynamic arrays to store accounts, pins, and balances.
  - `<conio.h>` for secure password input.
  - `<windows.h>` for additional functionalities like clearing the screen and adding delays.

## File Structure
- **atm.txt**: This file holds the user account data in the following format:
