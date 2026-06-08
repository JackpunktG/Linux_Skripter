# skript

A small CLI utility for storing and retrieving script/command aliases.

Scripts are stored in a binary database located at:

```text
data/data.b
```

---

## Building

Requirements:

* GCC or Clang
* Make

Build:

```bash
make
```

This creates the executable in the project root.

Example:

```text
.
├── skript
├── Makefile
├── data
├── lib
└── src
```

Clean build artifacts:

```bash
make clean
```

---

## Installation

Build the project:

```bash
make
```

Optional: install globally.

Linux:

```bash
sudo cp skript /usr/local/bin/
```

Verify:

```bash
skript
```

---

## Usage

### Add a script

```bash
skript -a build "make && ./app"
```

Stores the alias `build` with the script:

```text
make && ./app
```

### Print a script

```bash
skript -p build
```

Output:

```text
make && ./app
```

Useful for shell integration:

```bash
eval "$(skript -p build)"
```

### Remove a script

```bash
skript -r build
```

Removes the stored alias.

### Dump all scripts

```bash
skript -d
```

Output:

```text
build -> make && ./app
test  -> make test
run   -> ./app
```

---

## Commands

| Flag | Description                   |
| ---- | ----------------------------- |
| `-a` | Add a new alias and script    |
| `-r` | Remove an alias               |
| `-p` | Print the script for an alias |
| `-d` | Dump all stored aliases       |

---

## Examples

Add:

```bash
skript -a run "./app"
```

Print:

```bash
skript -p run
```

Remove:

```bash
skript -r run
```

List everything:

```bash
skript -d
```

---

## Data Format

The database file is stored as:

```c
u32 count;
Skript_Node entries[count];
```

where:

```c
typedef struct
{
    char alias[124];
    char skript[256];
} Skript_Node;
```

The file is rewritten whenever entries are added or removed.

---

## License

MIT
