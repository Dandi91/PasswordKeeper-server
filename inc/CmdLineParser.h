#ifndef CMDLINEPARSER_H
#define CMDLINEPARSER_H

#include "Main.h"
#include <wx/string.h>

const wxString sRunCmd     = "run";
const wxString sStopCmd    = "stop";
const wxString sStatCmd    = "stat";
const wxString sHelpCmd    = "help";

const wxString sPortArgL   = "--port";
const wxString sPortArgS   = "-p";
const wxString sConnArgL   = "--conn";
const wxString sConnArgS   = "-c";
const wxString sAccArgL    = "--acc";
const wxString sAccArgS    = "-a";

enum CmdLineCommand
{
  CMD_LINE_COMMAND_HELP = 0,
  CMD_LINE_COMMAND_RUN,
  CMD_LINE_COMMAND_STOP,
  CMD_LINE_COMMAND_STAT
};

const wxString Commands[] = {sHelpCmd, sRunCmd, sStopCmd, sStatCmd};

enum StatType
{
  STAT_TYPE_CONNECTIONS,
  STAT_TYPE_ACCOUNTS
};

class CmdLineParser
{
private:
  char** commandLine;
  int argCount;
  CmdLineCommand command;
  bool hasArgument;
  unsigned short port;
  StatType statType;
public:
  CmdLineParser(int argc, char** argv);
  void ShowUsage(const CmdLineCommand cmd = CMD_LINE_COMMAND_HELP);
  bool Parse();
  CmdLineCommand GetCommand() { return command; };
  unsigned short GetPort() { return hasArgument ? port : NET_DEFAULT_PORT; };
  StatType GetStatType() { wxASSERT(hasArgument); return statType; };
  bool HasArgument() { return hasArgument; };

protected:
private:
};

#endif // CMDLINEPARSER_H
