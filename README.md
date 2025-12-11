# Connect Labs

## 1. Περιγραφή Project

**Όνομα:** Connect Labs
**Μάθημα:** Προγραμματισμός Υπολογιστών με C++
**Βιβλιοθήκη γραφικών:** Simple Graphics Library (SGG)

**Ιδέα:**
Παιχνίδι τύπου *graph / connect-the-nodes*: ο παίκτης βλέπει ένα δίκτυο (γράφο) από “labs”/κόμβους και πρέπει, με βάση κάποιους κανόνες, να τα συνδέσει σωστά (μονοπάτια, περιορισμοί, στόχοι ανά level).

---

## 2. Τι έχει ήδη γίνει

* [x] Στήσιμο Visual Studio project (x64 / Debug).
* [x] Ενσωμάτωση βιβλιοθήκης SGG (libs + DLLs + include).
* [x] Δημιουργία βασικού παραθύρου SGG.
* [x] Φόρτωμα custom γραμματοσειράς και εμφάνιση κειμένου.

(Συμπλήρωσε κι άλλα αν χρειάζεται.)

---

## 3. Τι **πρέπει** να κάνουμε (υποχρεωτικά για την εργασία)

### 3.1 Αρχιτεκτονική & C++ features

* [ ] Σχεδιασμός βασικών classes:

  * [ ] `Game` (κεντρική λογική / game loop).
  * [ ] `Screen` / `State` (μενού, gameplay, κ.λπ.).
  * [ ] `Node` (κόμβος του γράφου).
  * [ ] `Edge` (σύνδεση / ακμή).
  * [ ] `Level` (φορτώνει / αποθηκεύει γράφο + στόχους).
* [ ] Χρήση **κληρονομικότητας** (π.χ. `Screen` → `MenuScreen`, `GameScreen`, `PauseScreen`)
* [ ] **Πολυμορφικές κλήσεις** (virtual methods π.χ. `update()`, `draw()` σε κοινή βάση).
* [ ] Χρήση STL **συλλογών** (π.χ. `std::vector`, `std::map`, `std::unordered_map` για nodes/edges/levels).

### 3.2 Μοντελοποίηση γράφου (network of labs)

* [ ] Αναπαράσταση κόμβων (`Node`, id, θέση στην οθόνη, κατάσταση).
* [ ] Αναπαράσταση ακμών (`Edge`, pointers ή ids των δύο κόμβων).
* [ ] Δομή δεδομένων:

  * [ ] `std::vector<Node>` για όλους τους κόμβους.
  * [ ] `std::vector<Edge>` ή `std::unordered_map<int, std::vector<int>>` για adjacency list.
* [ ] Συνάρτηση που ελέγχει τις συνδέσεις (valid moves, ολοκλήρωση level, κ.λπ.).

### 3.3 Core gameplay

* [ ] Ορισμός κανόνων παιχνιδιού (σε 2–3 προτάσεις στο README).
* [ ] Διαχείριση input:

  * [ ] Mouse click / drag για επιλογή κόμβων.
  * [ ] Highlight σε επιλεγμένο κόμβο / πιθανές συνδέσεις.
* [ ] Έλεγχος “νίκης” / “αποτυχίας” ενός level:

  * [ ] Έλεγχος αν ο γράφος έχει συγκεκριμένο μονοπάτι, βαθμό κόμβων, ή άλλο στόχο.
* [ ] Σύστημα score / stars / moves (ό,τι αποφασίσεις).

### 3.4 Screens / UI

* [ ] **Main Menu**:

  * [ ] κουμπί *Play*, *Options* (προαιρετικό), *Exit*.
* [ ] **Level Select**:

  * [ ] λίστα διαθέσιμων levels.
  * [ ] εμφάνιση locked/unlocked.
* [ ] **Game Screen**:

  * [ ] εμφάνιση grid / background.
  * [ ] σχεδίαση nodes & edges με SGG primitives.
  * [ ] HUD (κινήσεις, timer, level name).
* [ ] **Pause / Game Over Screen**:

  * [ ] κουμπί *Retry*, *Back to menu*.

### 3.5 Asset management

* [ ] Οργάνωση φακέλων:

  * [ ] `assets/fonts/`
  * [ ] `assets/textures/`
  * [ ] `assets/sounds/` (αν μπουν).
  * [ ] `assets/levels/` (π.χ. text/JSON-like αρχεία με περιγραφή γράφου).
* [ ] Φόρτωμα εικόνων σε σωστές διαστάσεις (κατά προτίμηση δυνάμεις του 2 για ταχύτερη φόρτωση).

### 3.6 Τελευταία φάση / Παράδοση

* [ ] Καθάρισμα κώδικα, σχόλια, διαχωρισμός header/implementation.
* [ ] Έλεγχος ότι το project χτίζεται **μόνο** με:

  * [ ] δικό μας κώδικα
  * [ ] `graphics.h`, `scancodes.h` από SGG (όχι ολόκληρη τη βιβλιοθήκη).
* [ ] Δημιουργία τελικού `.zip` με:

  * [ ] κώδικα,
  * [ ] assets,
  * [ ] οδηγίες εκτέλεσης.

---

## 4. Τι **θα θέλαμε** να κάνουμε (nice-to-have / επεκτάσεις)

* [ ] Σύστημα **προφίλ παίκτη** (save progress, unlocked levels).
* [ ] Animations (π.χ. όταν συνδέονται δύο labs).
* [ ] Ήχος:

  * [ ] click sound,
  * [ ] success / failure sound.
* [ ] Extra modes:

  * [ ] Time attack,
  * [ ] Puzzle editor (ο χρήστης φτιάχνει δικά του levels).
* [ ] Υποστήριξη πολλών “worlds” (themes με διαφορετικά backgrounds / χρώματα).
* [ ] Χρήση πιο προχωρημένων τεχνικών C++ (templates, custom containers) αν θες να δείξεις παραπάνω πράγματα.

---

## 5. Προτεινόμενη σειρά δουλειάς (μικρά βήματα)

1. **Σταθεροποίηση engine**: Game loop, states, basic input.
2. **Model γράφου**: `Node`, `Edge`, δομές STL.
3. **Ένα απλό level** hard-coded, μόνο για να παίζει ο μηχανισμός.
4. **Φόρτωμα levels από αρχείο**.
5. **UI + μενού**.
6. **Polish** (ήχοι, animations, καθάρισμα κώδικα).
7. **README τελικό** με screenshots, controls, περιγραφή.

---

Αν θέλεις, στο επόμενο μήνυμα μπορούμε να γράψουμε *μαζί* το κανονικό README.md (με markdown, sections, κτλ) με βάση αυτή τη λίστα.
