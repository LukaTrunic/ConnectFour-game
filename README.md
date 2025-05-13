# 🎮 Connect Four (C Console Game)

This is a console-based implementation of the classic **Connect Four** game developed in the C programming language using NetBeans IDE. The game allows two players to compete by dropping discs into a 7-column, 6-row grid and attempts to connect four of their pieces in a row.


## 🧠 Features

- 2-player mode with custom names
- 7x6 game board (standard Connect Four size)
- Input handling for column selection
- Board is printed after every turn
- Turn-based logic with alternating symbols ('X' and 'O')
- Victory detection for horizontal, vertical, and diagonal connections


## 🛠 How to Run

### Option 1: Compile manually
```bash
gcc main.c -o connect_four
./connect_four
```

### Option 2: Use NetBeans
- Open the project in NetBeans
- Build and run the project using the built-in tools


## 🎯 Game Controls

- Players are prompted to enter their name
- On each turn, input the column number (1–7) where the piece should drop
- The game checks for win conditions after each turn
- Invalid inputs are handled with warnings


## 🧾 Notes

- Uses simple arrays for game state tracking
- No external libraries beyond standard C headers
- Portable across systems that support C and `gcc`


## 📬 Author

Luka Trunić

