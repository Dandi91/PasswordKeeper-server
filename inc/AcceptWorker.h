#ifndef ACCEPTWORKER_H
#define ACCEPTWORKER_H

#include <wx/socket.h>
#include <wx/thread.h>
#include "Main.h"

class AcceptWorker : public wxThread
{
private:
public:
  AcceptWorker(const unsigned short port = NET_DEFAULT_PORT);
protected:
  virtual wxThread::ExitCode Entry();
};

#endif // ACCEPTWORKER_H
