#include "CmdLineParser.h"

const wxString sExeName    = "pkeep-server";
const wxString sUnknownArgMsg = "\"%s\" is unknown argument for '%s'\n";

CmdLineParser::CmdLineParser(int argc, char** argv)
{
  argCount = argc;
  commandLine = argv;
  command = CMD_LINE_COMMAND_HELP;
  port = NET_DEFAULT_PORT;
  hasArgument = false;
}

void CmdLineParser::ShowUsage(const CmdLineCommand cmd)
{
  switch (cmd)
  {
    case CMD_LINE_COMMAND_HELP:
    {
      wxPrintf("usage: %s command [<args>]\n\nAvailable commands are:\n", sExeName);
      wxPrintf("   %-8sRun server\n", sRunCmd);
      wxPrintf("   %-8sStop server\n", sStopCmd);
      wxPrintf("   %-8sDisplay server statistic\n", sStatCmd);
      wxPrintf("   %-8sDisplay this help\n", sHelpCmd);
      wxPrintf("\nBy default, without any command specified, '%s' command is used.\n", sHelpCmd);
      wxPrintf("Use '%s %s <command>' to see details and available arguments for the command.\n", sExeName, sHelpCmd);
      break;
    }
    case CMD_LINE_COMMAND_RUN:
    {
      wxPrintf("%s %s [%s=<port-num> | %s=<port-num>]\n\n", sExeName, sRunCmd, sPortArgL, sPortArgS);
      wxPrintf("Run server for listening to incoming clients. Available arguments:\n");
      wxPrintf("   %s=<port-num> | %s=<port-num>\n", sPortArgL, sPortArgS);
      wxPrintf("       Port number for listening to incoming connections. Default port is %d\n", NET_DEFAULT_PORT);
      wxPrintf("       Specified port number doesn't affect port number from the config file.\n");
      wxPrintf("\nIf no argument is specified, the port number from the config file is used.\n");
      break;
    }
    case CMD_LINE_COMMAND_STOP:
    {
      wxPrintf("%s %s\n\n", sExeName, sStopCmd);
      wxPrintf("Stop server if it is running. This command takes no arguments.\n");
      break;
    }
    case CMD_LINE_COMMAND_STAT:
    {
      wxPrintf("%s %s [%s | %s | %s | %s]\n\n", sExeName, sStatCmd, sConnArgL, sConnArgS, sAccArgL, sAccArgS);
      wxPrintf("Show server statistics. Available arguments:\n");
      wxPrintf("   %s | %s\n", sConnArgL, sConnArgS);
      wxPrintf("       Show information about currently connected clients\n");
      wxPrintf("   %s | %s\n", sAccArgL, sAccArgS);
      wxPrintf("       Show information about currently stored accounts\n");
      wxPrintf("\nIf no argument is specified, show only server status (whether it's run or stopped).\n");
      break;
    }
  }
}

bool CmdLineParser::Parse()
{
  if (argCount < 2)
  {
    // No parameters specified. 'help' is used by default
    command = CMD_LINE_COMMAND_HELP;
    ShowUsage();
    return true;
  }
  // Get command
  wxString cmd = commandLine[1];
  if (cmd == sRunCmd)
    command = CMD_LINE_COMMAND_RUN;
  else if (cmd == sStopCmd)
    command = CMD_LINE_COMMAND_STOP;
  else if (cmd == sStatCmd)
    command = CMD_LINE_COMMAND_STAT;
  else if (cmd == sHelpCmd)
    command = CMD_LINE_COMMAND_HELP;
  else
  {
    ShowUsage();
    return false;
  }
  if (argCount == 2)
  {
    if (command == CMD_LINE_COMMAND_HELP)
      ShowUsage();
    return true;
  }
  if (argCount == 3)
  {
    // The command has an argument
    hasArgument = true;
    wxString arg = commandLine[2];
    switch (command)
    {
      case CMD_LINE_COMMAND_RUN:
      {
        // Argument is a port number
        if ((arg.Before('=') == sPortArgL) || (arg.Before('=') == sPortArgS))
        {
          unsigned long longPort = 0;
          arg.After('=').ToULong(&longPort);
          port = longPort;
          return true;
        }
        else
        {
          // Unknown argument for 'run'
          wxPrintf(sUnknownArgMsg, arg, sRunCmd);
          ShowUsage(CMD_LINE_COMMAND_RUN);
          return false;
        }
      }
      case CMD_LINE_COMMAND_STOP:
      {
        // Unknown argument for 'stop'
        wxPrintf(sUnknownArgMsg, arg, sStopCmd);
        ShowUsage(CMD_LINE_COMMAND_STOP);
        return false;
      }
      case CMD_LINE_COMMAND_STAT:
      {
        // Argument is a statistic type
        if ((arg == sConnArgL) || (arg == sConnArgS))
        {
          statType = STAT_TYPE_CONNECTIONS;
          return true;
        }
        else if ((arg == sAccArgL) || (arg == sAccArgS))
        {
          statType = STAT_TYPE_ACCOUNTS;
          return true;
        }
        else
        {
          // Unknown argument for 'stat'
          wxPrintf(sUnknownArgMsg, arg, sStatCmd);
          ShowUsage(CMD_LINE_COMMAND_STAT);
          return false;
        }
        break;
      }
      case CMD_LINE_COMMAND_HELP:
      {
        // Argument is a command
        if (arg == sRunCmd)
        {
          ShowUsage(CMD_LINE_COMMAND_RUN);
          return true;
        }
        else if (arg == sStopCmd)
        {
          ShowUsage(CMD_LINE_COMMAND_STOP);
          return true;
        }
        else if (arg == sStatCmd)
        {
          ShowUsage(CMD_LINE_COMMAND_STAT);
          return true;
        }
        else
        {
          // Unknown argument for 'help'
          ShowUsage();
          return false;
        }
        break;
      }
    }
  }
  else
  {
    // Wrong argument count
    ShowUsage();
    return false;
  }
  return true;
}
