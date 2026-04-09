### *Personal Savings Account System*

<br/>

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![WebAssembly](https://img.shields.io/badge/WebAssembly-654FF0?style=for-the-badge&logo=webassembly&logoColor=white)
![GitHub Pages](https://img.shields.io/badge/GitHub%20Pages-222222?style=for-the-badge&logo=github&logoColor=white)
![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)

<br/>

![Status](https://img.shields.io/badge/Status-Live%20%26%20Deployed-C9A84C?style=flat-square&logo=checkmarx&logoColor=white)
![Assignment](https://img.shields.io/badge/Assignment-DA2%20%7C%20OOP-C9A84C?style=flat-square&logo=academia&logoColor=white)
![University](https://img.shields.io/badge/VIT-Chennai-C9A84C?style=flat-square&logo=google-scholar&logoColor=white)
![Language](https://img.shields.io/badge/C%2B%2B-OOP%20Based-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Compiler](https://img.shields.io/badge/Compiler-em%2B%2B%20%7C%20Emscripten-654FF0?style=flat-square&logo=webassembly&logoColor=white)

<br/>

> **A cooperative society savings account system built in C++ with full OOP architecture,**  
> **compiled to WebAssembly and deployed as a live interactive web application.**

<br/>

[**🌐 Live Demo**](#-live-demo) · [**⚙️ Build**](#️-build-instructions) · [**🏛️ Architecture**](#️-oop-architecture) · [**✨ Features**](#-features)

---

</div>

<br/>

## 🏦 Overview

**Imperial Bank** is a DA2 mini-project for the *Object-Oriented Programming* course at **VIT Chennai**. It simulates a real-world cooperative savings account system with full CRUD operations, persistent file storage, and a premium terminal-style web UI — all powered by a C++ backend compiled to **WebAssembly** via Emscripten.

The system demonstrates core C++ OOP concepts: **encapsulation**, **data hiding**, **abstraction**, **modularity**, and **STL usage** — while being fully accessible from any browser with no installation required.

<br/>

## 🌐 Live Demo

> ⚡ Runs entirely in your browser via WebAssembly — no server, no backend.

```
🔗 https://<your-username>.github.io/<your-repo-name>/
```

<div align="center">

| Interface | Description |
|-----------|-------------|
| 🖥️ Terminal Ledger | Color-coded output mimicking a real banking console |
| 🪟 Modal Dialogs | Form-based input for all operations — no CLI confusion |
| 📊 Live Stats Strip | Real-time account count, total funds, transaction count |
| 💾 Persistent Storage | Data survives page refreshes via browser `localStorage` |

</div>

<br/>

## ✨ Features

<div align="center">

| # | Feature | Description |
|---|---------|-------------|
| `1` | 🆕 **Create Account** | Unique AccNo, name, mobile, email, opening balance |
| `2` | 💚 **Deposit** | Validated deposits with transaction reference |
| `3` | 🔴 **Withdraw** | Overdraft protection enforced at object level |
| `4` | 🔍 **Balance Enquiry** | Full account details with contact info |
| `5` | 📜 **Transaction History** | Last N records with date, type, ref number |
| `6` | 📋 **All Accounts** | Tabular list with balances and mobile numbers |
| `7` | 💰 **Total Funds Report** | Aggregate across all accounts |
| `8` | ⚠️ **Low Balance Report** | Threshold-based filter |
| `9` | ✏️ **Edit Account** | Update name, mobile, email — AccNo & balance locked |
| `DEL` | 🗑️ **Delete Account** | Requires `DELETE` confirmation, removes all transactions |

</div>

<br/>

## 🏛️ OOP Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                        BankSystem                            │
│  ┌──────────────────────────────────────────────────────┐   │
│  │  vector<Account>          vector<Transaction>        │   │
│  │  ┌──────────────┐         ┌────────────────────┐     │   │
│  │  │   Account    │         │    Transaction     │     │   │
│  │  │ ──────────── │         │ ────────────────── │     │   │
│  │  │ - accNo      │         │  + txnId           │     │   │
│  │  │ - name       │         │  + accNo           │     │   │
│  │  │ - balance    │◄────────│  + type            │     │   │
│  │  │ - mobile     │         │  + amount          │     │   │
│  │  │ - email      │         │  + balanceAfter    │     │   │
│  │  │ ──────────── │         │  + dateTime        │     │   │
│  │  │ + deposit()  │         └────────────────────┘     │   │
│  │  │ + withdraw() │                                     │   │
│  │  │ + getters()  │    File I/O: accounts.txt           │   │
│  │  └──────────────┘           transactions.txt          │   │
│  └──────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

### Class Breakdown

| Class | Responsibility | OOP Concept |
|-------|---------------|-------------|
| `Transaction` | Immutable record of one financial event | Data encapsulation |
| `Account` | Private balance — modified only via `deposit()`/`withdraw()` | Encapsulation + Data hiding |
| `BankSystem` | Orchestrates all operations, file persistence, STL containers | Abstraction + Modularity |

### Why C++ over C?

| C | C++ (This Project) |
|---|---------------------|
| `struct` with no methods | `class` with private data + public methods |
| Manual memory management | `vector<T>` — automatic, safe, resizable |
| Global functions for logic | Member functions — data and behavior together |
| No constructor guarantees | Constructors ensure valid initial state |
| No encapsulation | `private:` blocks prevent direct balance tampering |

<br/>

## 📁 Repository Structure

```
📦 coopbank/
 ┣ 📄 main.cpp         ← Full C++ source — 3 classes, OOP design
 ┣ 📄 index.html       ← Custom Imperial Bank UI shell
 ┣ 📄 index.js         ← Generated by em++ · DO NOT EDIT
 ┣ 📄 index.wasm       ← WebAssembly binary · DO NOT EDIT
 ┗ 📄 README.md        ← You are here
```

<br/>

## ⚙️ Build Instructions

### Prerequisites

```bash
# Check if you have these installed
git --version       # git 2.x+
python --version    # Python 3.x
em++ -v             # Emscripten (install below if missing)
```

### 1 · Install Emscripten (Windows)

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
emsdk install latest
emsdk activate latest
emsdk_env.bat        # Run this every new terminal session
```

### 2 · Compile to WebAssembly

```bash
# Navigate to your project folder
cd your-project-folder

# Compile with Asyncify for proper stdin support
em++ main.cpp -o index.html \
  -sASYNCIFY=1 \
  -sASYNCIFY_IMPORTS="['emscripten_sleep']" \
  -sFORCE_FILESYSTEM=1 \
  -sEXIT_RUNTIME=0 \
  -O2
```

> ⚠️ This generates a new `index.html` — **replace it** with the custom `index.html` from this repo.  
> Keep `index.js` and `index.wasm` as-is.

### 3 · Test Locally

```bash
# Serve locally (WASM requires a server, not file://)
python -m http.server 8080

# Open in browser
http://localhost:8080
```

<br/>

## 🚀 Deploy to GitHub Pages

```
Step 1 ─── Create a PUBLIC repository on GitHub
            e.g. coopbank-da2

Step 2 ─── Upload these 4 files:
            index.html  ·  index.js  ·  index.wasm  ·  main.cpp

Step 3 ─── Settings → Pages → Source: Deploy from branch
            Branch: main  ·  Folder: / (root)  →  Save

Step 4 ─── Wait 2–5 minutes ☕

Step 5 ─── Your live link:
            https://<username>.github.io/<repo-name>/
```

> **If you see a 404:** Make sure the repo is public and Pages is enabled. GitHub can take a few minutes on first deploy.

<br/>

## 🧪 Test Cases

| # | Input | Expected | Type |
|---|-------|----------|------|
| TC01 | Create Acc #1001, "Ravi", ₹5000 | Account created successfully | ✅ Normal |
| TC02 | Create Acc #1001 again | "Already exists" error | 🔁 Duplicate |
| TC03 | Deposit -500 to #1001 | "Invalid amount" error | ❌ Invalid |
| TC04 | Withdraw ₹99999 from #1001 | "Insufficient funds" error | ❌ Boundary |
| TC05 | Withdraw ₹3000 from #1001 | Success, balance = ₹2000 | ✅ Normal |
| TC06 | Balance enquiry on #9999 | "Account not found" error | ❌ Not Found |
| TC07 | Delete #1001, type "DELETE" | Account and txns removed | ✅ Delete |
| TC08 | Delete #1001, type "delete" | Blocked — case mismatch | 🔒 Security |
| TC09 | Low balance report, threshold ₹500 | Lists all accs below ₹500 | ✅ Report |
| TC10 | Edit #1001 — change name | Name updated, balance locked | ✅ Edit |

<br/>

## 📐 STL Usage

| Container | Used For | Why Not Array? |
|-----------|----------|----------------|
| `vector<Account>` | Dynamic list of all accounts | No fixed size; supports `emplace_back`, `find_if`, `erase` |
| `vector<Transaction>` | Transaction log | Grows unboundedly; easy filter/slice for history |
| `string` | All text fields | Handles arbitrary length, `.trim()`, concatenation safely |
| `stringstream` | CSV parsing for file I/O | Clean tokenizing without `strtok` memory risks |
| `ostringstream` | Formatting TXN ref codes | Type-safe `setw`/`setfill` formatting |

<br/>

## 📂 File Storage Format

**`accounts.txt`** — one account per line:
```
1001,Ravi Kumar,5000.000000,9876543210,ravi@email.com
1002,Priya Singh,12500.500000,8765432109,priya@email.com
```

**`transactions.txt`** — one transaction per line:
```
1,1001,DEPOSIT,5000.000000,5000.000000,01/01/2025 10:30
2,1001,WITHDRAW,2000.000000,3000.000000,01/01/2025 11:15
3,1002,DEPOSIT,12500.500000,12500.500000,02/01/2025 09:00
```

> Format: `txnId,accNo,type,amount,balanceAfter,dateTime`

<br/>

## 🤖 AI Usage Declaration

| Question | Answer |
|----------|--------|
| Did you use AI? | Yes — ChatGPT / Claude for reference |
| For which part? | UI design guidance, Emscripten stdin debugging |
| Modifications made? | Full OOP logic written and understood independently; UI significantly customized |
| Self-debugging done? | Fixed Asyncify `cin >>` bug, IDBFS persistence, modal input flow |
| Understanding demonstrated? | Can explain every class method, memory model, and STL choice |

<br/>

## 🛠️ Challenges Faced

**1 · Emscripten stdin blocking** — `cin >>` occupies the WASM thread and blocks the JS event loop entirely. Fixed by replacing all `cin >>` with `getline()`-based helpers and adding `WASM_YIELD()` macros with `-sASYNCIFY=1`.

**2 · `cin.ignore()` + `getline()` bug** — After `cin >> accNo`, a `\n` is left in the buffer causing `getline` to return empty on the next read. Resolved by eliminating all `cin >>` and using only line-based reads.

**3 · OOP design challenge** — Initially put file I/O logic inside `Account`. Refactored to keep `Account` purely about data/behavior, with `BankSystem` owning all persistence — proper separation of concerns.

**4 · GitHub Pages 404** — First deploy failed silently. Root cause: repo was private. Fixed by making it public and re-enabling Pages.

**5 · WebAssembly CORS restrictions** — `file://` protocol blocks WASM loading. Required running a local Python server (`python -m http.server`) during development.

**6 · Balancing WASM + JS** — The web frontend (JS) and the C++ backend (WASM) needed to stay in sync. Solved by keeping C++ as the source of truth for business logic and mirroring the class design in JS for the live UI layer.

<br/>

## 📚 What I Learned

```
Object-Oriented Design  →  Classes are more than structs — they bundle data + behaviour
Encapsulation           →  private balance means only deposit()/withdraw() can change it
STL Power               →  vector + string beat raw arrays for every real-world use case
File Handling           →  fstream CSV gives persistent state without a database
WebAssembly             →  C++ can run in a browser — the future of portable computation
Asyncify                →  Bridging synchronous C++ blocking I/O with async JS event loop
```

<br/>

<div align="center">

---



![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![WebAssembly](https://img.shields.io/badge/WebAssembly-654FF0?style=for-the-badge&logo=webassembly&logoColor=white)
![GitHub Pages](https://img.shields.io/badge/Hosted%20on-GitHub%20Pages-222222?style=for-the-badge&logo=github&logoColor=white)

</div>
