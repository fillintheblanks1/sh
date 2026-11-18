#include "executor.h"
#include <vector>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <iostream>

int runProgram(const std::string &fullPath,
               const std::vector<std::string> &words) {
  std::string commandLine = "\"" + fullPath + "\"";
  for (size_t i = 1; i < words.size(); i++) {
    commandLine += " " + words[i];
  }


  STARTUPINFOA si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si); // Windows checks this to know which version of the struct
  ZeroMemory(&pi, sizeof(pi));

  // 3. CreateProcessA needs a writable buffer, so copy the string into one
  std::vector<char> buffer(commandLine.begin(), commandLine.end());
  buffer.push_back('\0');

  BOOL ok = CreateProcessA(nullptr,       // program name (taken from the command line)
                           buffer.data(), // command line
                           nullptr,       // process security
                           nullptr,       // thread security
                           FALSE,         // don't inherit handles (yet)
                           0,             // creation flags
                           nullptr,       // use our environment
                           nullptr,       // use our current directory
                           &si, &pi);

  if (!ok) {
    std::cerr << "mysh: failed to run " << fullPath << " (error "
              << GetLastError() << ")" << std::endl;
    return 1;
  }

  // until the program finishes
  WaitForSingleObject(pi.hProcess, INFINITE);

  // read its exit code
  DWORD code = 0;
  GetExitCodeProcess(pi.hProcess, &code);

  // release the handles
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  return static_cast<int>(code);
}