# 🏛️ FEmulator — Global Open-Source Multiplatform Architecture

This is the primary repository of **FEmulator** (FDevelop's Emulator), managed under the operational frameworks of the **FDevelop Studio** virtual organization. The project is designed as a modular, decentralized, high-performance solution combining Kotlin Multiplatform with a native low-level backend.

---

## ⚙️ 1. REPOSITORY STRUCTURE (TOOLCHAIN LAYOUT)

The repository leverages a unified modern layout utilizing independent application modules linked to an isolated shared logical core:

*   **`shared`** — The primary shared core module. Contains the cross-platform microarchitecture simulation logic, processor registers math, and unified Material 3 UI states.
*   **`desktopApp`** — A standalone execution wrapper compiling an ultra-fast JVM desktop window for Windows 11, macOS, and Linux targets.
*   **`androidApp`** — An isolated production mobile container leveraging Google's **AGP 9.3.1 New DSL** pipelines (`android.newDsl=true`).

---

## 🛠️ 2. SYSTEM ARCHITECTURE & ENVIRONMENT TARGETS

To ensure absolute build stability and performance reproducibility across distributed team members, the following global specifications are locked:

1.  **Language Standard:** Kotlin **2.4.10** compiler runtime engine (K2 analytical mode enabled).
2.  **UI Core Framework:** Compose Multiplatform **1.11.1** layout platform.
3.  **Data Sync Layer:** Supabase **3.7.0** architecture utilizing unified Bill of Materials (`BOM`) dependency graphs and Ktor **3.0.0** CIO clients.
4.  **Hardware Target Platform:** Java **21+** runtime bytecode layout to natively support low-overhead **Project Panama** (Foreign Function & Memory API) C++ bindings.

---

## ⚖️ 3. LEGAL POLICY & LICENSE WRAPPERS

*   **Licensing Terms:** The entire source code layout across all execution targets is strictly protected and distributed under the **GNU GPL v3** copyleft license matrix.
*   **Compliance:** Refer to `EULA.md` and `LICENSE.md` files for explicit specifications regarding downstream repository modifications, trademark mandates, and binary image distributions.