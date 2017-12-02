#include <iostream>
#include <vector>

#include <string>

#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <limits.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

#define DEFAULT_TIME 20
#define G "\033[32m"

static int signalSIGINT = 0;
static int signalSIGQUIT = 0;
static int signalSIGHUP = 0;
static int signalSIGTERM = 0;
static int signalSIGABRT = 0;
static int signalSIGCONT = 0;
static int signalSIGTSTP = 0;

std::vector<std::string> instructions;

static void initInstructions(void) {
  instructions.push_back("instruction 1");
  instructions.push_back("instruction 2");
  instructions.push_back("instruction 3");
  instructions.push_back("instruction 4");
  instructions.push_back("instruction 5");
  instructions.push_back("instruction 6");
  instructions.push_back("instruction 7");
  instructions.push_back("instruction 8");
  instructions.push_back("instruction 9");
  instructions.push_back("instruction 10");
  instructions.push_back("instruction 11");
  instructions.push_back("instruction 12");
  instructions.push_back("instruction 13");
  instructions.push_back("instruction 14");
  instructions.push_back("instruction 15");
  instructions.push_back("instruction 16");
  instructions.push_back("instruction 17");
  instructions.push_back("instruction 18");
  instructions.push_back("instruction 19");
  instructions.push_back("instruction 20");
  instructions.push_back("instruction 21");
  instructions.push_back("instruction 22");
  instructions.push_back("instruction 23");
  instructions.push_back("instruction 24");
  instructions.push_back("instruction 25");
  instructions.push_back("instruction 26");
  instructions.push_back("instruction 27");
  instructions.push_back("instruction 28");
  instructions.push_back("instruction 29");
  instructions.push_back("instruction 30");
  instructions.push_back("instruction 31");
  instructions.push_back("instruction 32");
  instructions.push_back("instruction 33");
  instructions.push_back("instruction 34");
  instructions.push_back("instruction 35");
  instructions.push_back("instruction 36");
  instructions.push_back("instruction 37");
  instructions.push_back("instruction 38");
  instructions.push_back("instruction 39");
  instructions.push_back("instruction 40");
  instructions.push_back("instruction 41");
  instructions.push_back("instruction 42");
  instructions.push_back("instruction 43");
  instructions.push_back("instruction 44");
  instructions.push_back("instruction 45");
  instructions.push_back("instruction 46");
  instructions.push_back("instruction 47");
  instructions.push_back("instruction 48");
  instructions.push_back("instruction 49");
  instructions.push_back("instruction 50");
}

static void trap(int s) {
  switch (s) {
  case SIGINT:
    signalSIGINT = 1;
    break;
  case SIGQUIT:
    signalSIGQUIT = 1;
    break;
  case SIGHUP:
    signalSIGHUP = 1;
    break;
  case SIGCONT:
    signalSIGCONT = 1;
    break;
  case SIGTSTP:
    signalSIGTSTP = 1;
    break;
  case SIGABRT:
    signalSIGABRT = 1;
    break;
  case SIGTERM:
    signalSIGTERM = 1;
    break;
  }
}

void trap_hook_signal(void) {
  signal(SIGINT, trap);
  signal(SIGQUIT, trap);
  signal(SIGHUP, trap);
  signal(SIGTERM, trap);
  signal(SIGABRT, trap);
  signal(SIGTSTP, trap);
}

int set_num_instructions(int argc, char *argv[]) {
  int cycles = argc < 2 ? DEFAULT_TIME : atoi(argv[1]);
  cycles = cycles <= 0 ? 1 : cycles;
  return cycles;
}

void printInit(pid_t pid) {
  std::cout << G << "Process " << (int)pid << "  STARTED";
  std::cout.flush();
}

void printSIGCONT(pid_t pid) {
  signalSIGCONT = 0;
  std::cout << G << "Process " << (int)pid << "  return " << G << "SIGCONT"
            << std::endl;
  std::cout.flush();
}

std::string fetchInstruction(void) {
  srand((unsigned)time(0));
  int pos = (rand() % instructions.size());
  return instructions[pos];
}

void printINSTRUCTION(pid_t pid, int i) {
  std::string ins = fetchInstruction();
  std::cout << G << "Process " << (int)pid << "  " << ins << std::endl;
  ;
  std::cout.flush();
}

void printSIGINT(pid_t pid) {
  std::cout << G << "Process " << (int)pid << "  return "
            << "SIGINT" << std::endl;
  std::cout.flush();
  exit(0);
}

void printSIGQUIT(pid_t pid) {
  std::cout << G << "Process " << (int)pid << "  return "
            << "SIGQUIT" << std::endl;
  std::cout.flush();
  exit(0);
}

void printSIGHUP(pid_t pid) {
  std::cout << G << "Process " << (int)pid << " return "
            << "SIGHUP" << std::endl;
  std::cout.flush();
  exit(0);
}

void printSIGTSTP(pid_t pid) {
  sigset_t mask;
  signalSIGTSTP = 0;
  std::cout << G << "Process " << (int)pid << "  return "
            << "SIGTSTP" << std::endl;
  std::cout.flush();
  sigemptyset(&mask);
  sigaddset(&mask, SIGTSTP);
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
  signal(SIGTSTP, SIG_DFL);
  raise(SIGTSTP);
  signal(SIGTSTP, trap);
  signalSIGCONT = 1;
}

void printSIGABRT(pid_t pid) {
  std::cout << G << "PID[" << (int)pid << G << "]";
  std::cout << G << "  return "
            << "SIGABRT" << std::endl;
  std::cout.flush();
  signal(SIGABRT, SIG_DFL);
  raise(SIGABRT);
}

void printSIGTERM(pid_t pid) {
  std::cout << G << "Process " << (int)pid << "  return "
            << "SIGTERM" << std::endl;
  std::cout.flush();
  exit(0);
}

bool isStillRunning(void) {
  clock_t starttick, stoptick;
  struct tms t;
  int rc = setpriority(PRIO_PROCESS, 0, 20);
  long clktck = sysconf(_SC_CLK_TCK);
  starttick = times(&t);
  rc = sleep(1);
  stoptick = times(&t);
  return (rc == 0 || ((stoptick - starttick) > clktck / 2));
}

void execute_instruction(pid_t pid, int i) {
  if (signalSIGCONT)
    printSIGCONT(pid);
  if (isStillRunning())
    printINSTRUCTION(pid, i);
  if (signalSIGINT)
    printSIGINT(pid);
  if (signalSIGQUIT)
    printSIGQUIT(pid);
  if (signalSIGHUP)
    printSIGHUP(pid);
  if (signalSIGTSTP)
    printSIGTSTP(pid);
  if (signalSIGABRT)
    printSIGABRT(pid);
  if (signalSIGTERM)
    printSIGTERM(pid);
}

int main(int argc, char *argv[]) {
  pid_t pid = getpid();
  printInit(pid);
  initInstructions();
  trap_hook_signal();
  int cycle = set_num_instructions(argc, argv);
  for (int i = 0; i < cycle; i++) {
    execute_instruction(pid, i);
  }
  exit(0);
}
