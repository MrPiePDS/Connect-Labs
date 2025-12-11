# **Connect Labs**

Ένα μικρό παιχνίδι / προσομοίωση βασισμένο στην ιδέα των Upload Labs, φτιαγμένο για την εργασία «Διαδραστική Εφαρμογή με Χρήση Δικτύου Κόμβων» στο μάθημα Προγραμματισμού Υπολογιστών με C++ .

Στόχος είναι να δημιουργήσουμε ένα σύστημα από “Labs” (κόμβους) τα οποία συνδέονται μεταξύ τους και διακινούν πακέτα δεδομένων. Ο παίκτης καλείται να στήσει σωστά τις συνδέσεις ώστε τα δεδομένα να φτάσουν στον προορισμό τους, χωρίς overflow ή λάθος ροή.

Η εφαρμογή χτίζεται εξ ολοκλήρου με τη **Simple Graphics Library (SGG)** που δίνεται στο μάθημα και δεν χρησιμοποιεί άλλη εξωτερική γραφική βιβλιοθήκη (υποχρεωτικό σύμφωνα με την εκφώνηση) .

---

# **Gameplay – Τι είναι το Connect Labs**

Το παιχνίδι διαδραματίζεται πάνω σε ένα grid.
Ο χρήστης μπορεί να τοποθετεί Labs, να τα συνδέει με γραμμές (edges) και να βλέπει πακέτα δεδομένων (packets) να κινούνται στο δίκτυο.

Κάθε Lab έχει διαφορετικό ρόλο:

* Upload Lab → παράγει πακέτα
* Processor Lab → τα επεξεργάζεται
* Filter Lab → αφήνει μόνο ορισμένα
* Splitter / Merger
* Destination Lab → ο τελικός στόχος του level

Οι στόχοι κάθε level μπορεί να είναι:

* να φτάσουν Χ πακέτα στον προορισμό
* να μην υπερχειλίσουν buffers
* να πετύχεις συγκεκριμένη ροή (throughput)
* να φτιάξεις σωστή διαδρομή δεδομένων

Η αισθητική και η λειτουργία είναι εμπνευσμένη από **Upload Labs**, αλλά ο κώδικας είναι εξ ολοκλήρου δικός μας.

---

# **Τι έχουμε κάνει μέχρι τώρα**

* Δημιουργήσαμε το VS Project με την SGG
* Το παράθυρο λειτουργεί σε Windows subsystem
* Φορτώνεται custom γραμματοσειρά (TTF)
* Υλοποιήσαμε grid background
* Αρχίσαμε τη σχεδίαση UI elements
* Προετοιμάσαμε χώρο και δομή για Nodes, Edges και Packets

---

# **Τι πρέπει να υποστηρίζει το project (σύμφωνα με την εκφώνηση)**

Παρακάτω είναι συνοπτικά όλα τα **υποχρεωτικά** σημεία που απαιτεί η εργασία (πηγή: σελ. 4–6 του PDF) :

### Χρήση της βιβλιοθήκης SGG

Αποκλειστική χρήση της SGG για παράθυρο, graphics, input.

### Δυναμική μνήμη (new/delete)

Labs, Packets και άλλα entities πρέπει να δημιουργούνται δυναμικά.

### Κληρονομικότητα & Πολυμορφισμός

Όλα τα οπτικά στοιχεία και στοιχεία του γραφήματος πρέπει να οργανωθούν ιεραρχικά.

Παράδειγμα:
`Node` → `UploaderNode`, `ProcessorNode`, `FilterNode`, κ.λπ.

Με κοινές virtual μεθόδους:

```cpp
virtual void update(float dt) = 0;
virtual void draw() = 0;
```

### Χρήση STL Συλλογών

Χρειαζόμαστε δομές όπως:

* `std::vector<Node*>`
* `std::unordered_map<int, std::vector<int>>`
* `std::vector<Packet*>`

### GlobalState (υποχρεωτικό)

Πρέπει να υπάρχει **ένα** αντικείμενο που:

* κρατάει όλα τα Nodes, Edges, Packets
* αποθηκεύει ποιο level παίζουμε
* έχει methods `update()`, `draw()`, `init()`
* λειτουργεί ως “κεντρικός εγκέφαλος” του παιχνιδιού

Αυτό αναφέρεται ρητά στην εκφώνηση σελ. 5 .

### Collision / selection

Πρέπει να γίνει ανίχνευση επιλογής με το ποντίκι:

* point-in-rect (σελ. 6 του PDF)
* point-in-circle (σελ. 6)

---

# **Πώς θα οργανωθεί ο κώδικας**

Μια απλή και καθαρή δομή project:

```
src/
  main.cpp
  GameState.h / GameState.cpp
  Screen.h
  MenuScreen.cpp
  GameplayScreen.cpp
  Node.h / Node.cpp
  UploaderNode.h / UploaderNode.cpp
  ProcessorNode.h / ProcessorNode.cpp
  Edge.h / Edge.cpp
  Packet.h / Packet.cpp

assets/
  fonts/
  icons/
  levels/

README.md
```

---

# 🛠️ **Πώς δουλεύουμε μέσα από το GitHub**

Για να είναι ξεκάθαρη η συνεργασία και το ιστορικό ανάπτυξης, ακολουθούμε μια απλή ροή:

### 1️. Main branch = σταθερή κατάσταση

Ό,τι δουλεύει και παίζει σωστά μπαίνει στο `main`.

### 2️. Feature branches

Για κάθε νέο υποσύστημα φτιάχνουμε νέο branch:

* `feature/grid`
* `feature/nodes`
* `feature/packet-flow`
* `feature/ui`
* `feature/level-loader`
* `feature/global-state`

### 3️. Κάθε commit = μικρή αλλαγή με νόημα

Παράδειγμα commit messages:

* ✦ “Added Grid Rendering System”
* ✦ “Initial Node class + draw() method”
* ✦ “Implemented dynamic Packet allocation”
* ✦ “Added GlobalState skeleton”

### 4️. Pull Requests για συγχώνευση

Όταν ολοκληρώνουμε κάτι:

* ανοίγουμε PR
* περιγράφουμε τι προστέθηκε
* κάνουμε merge όταν είναι stable

### 5️. Releases (προαιρετικά)

Κάθε σημαντικό milestone (π.χ. Level 1 playable) μπορεί να γίνει release στο GitHub.

---

# **Ποια είναι η σειρά που θα το χτίσουμε**

Μια ρεαλιστική σειρά εργασίας για να μην μπλέξουμε:

### **PHASE 1 – Foundations**

* [ ] Grid
* [ ] Rendering basics
* [ ] GameState skeleton
* [ ] Screens system

### **PHASE 2 – Graph Logic**

* [ ] Node class + derived classes
* [ ] Edge class
* [ ] Packet class
* [ ] Dynamic memory flow

### **PHASE 3 – Gameplay**

* [ ] Packet routing
* [ ] Node processing logic
* [ ] Buffers / throughput
* [ ] Win conditions

### **PHASE 4 – Interaction**

* [ ] Mouse selection
* [ ] Drag & drop nodes
* [ ] Connect nodes with edges

### **PHASE 5 – UI**

* [ ] Menu
* [ ] Level select
* [ ] HUD, panels, info boxes

### **PHASE 6 – Polish**

* [ ] Animations
* [ ] Sounds
* [ ] Level files
* [ ] Balancing

---

# **Σημείωση για την παράδοση**

Σύμφωνα με τις οδηγίες (σελ. 8–9) πρέπει να παραδώσουμε:

* τον κώδικα (χωρίς τα .dll/.lib/.obj .pdb)
* μόνο τα `graphics.h` & `scancodes.h` από SGG
* τα assets (π.χ. `assets/`)
* το project (.sln / .vcxproj)
* zip με σωστή δομή
* README (αυτό εδώ)



---

# **Τελικό με λίγα λόγια**

Το Connect Labs είναι:

* ένα παιχνίδι puzzle / simulation με ροή δεδομένων
* υλοποιημένο 100% σε C++
* με χρήση γράφων (nodes & edges)
* με OOP αρχιτεκτονική και polymorphism
* με dynamic memory
* και rendering/interaction μέσω SGG

Και θα αναπτυχθεί κομμάτι–κομμάτι μέσα από το GitHub.

---
