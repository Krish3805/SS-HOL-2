# SS_HOL2 — OS Lab Hand-On-Lab 2

**Author:** Krish Vaghasiya
**Course:** EGC 301P — Operating System Lab (M.Tech Sem 1)
**Date:** October 2026

## Overview
Solutions for OS Lab exercises **Q31-Q64** covering:
- **Section III** (Q31-Q52): System V IPC — Pipes, FIFOs, Message Queues, Shared Memory, Semaphores, Sockets
- **Section IV** (Q53-Q64): Timers, Resource Limits, Multithreading, Signals

All programs live together in the `programs/` folder. Each program is named after its syllabus question, e.g. `31.c` = Q31, `44a.c` = Q44(a), `59c.c` = Q59(c).

## Build
```bash
cd programs
gcc -o 31 31.c && ./31
```
Run programs from inside `programs/`, since some of them use relative files (`progfile`, `shmfile`, FIFOs). Create `progfile`/`shmfile` first with `touch` where a program asks for it.

## Program Map
| Programs | Q#      | Topic               |
|----------|---------|---------------------|
| 31-35  | Q31-Q35 | Anonymous Pipes     |
| 36-39  | Q36-Q39 | Named Pipes (FIFOs) |
| 40     | Q40     | Pipe limits         |
| 41-46  | Q41-Q46 | Message Queues      |
| 47     | Q47     | Shared Memory       |
| 48-50  | Q48-Q50 | Semaphores          |
| 51-52  | Q51-Q52 | Sockets             |
| 53     | Q53     | Interval Timers     |
| 54-57  | Q54-Q57 | Resource Limits     |
| 58     | Q58     | Multithreading      |
| 59-64  | Q59-Q64 | Signal Handling     |
