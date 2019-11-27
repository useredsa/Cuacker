#ifndef AEDI_INTERPRETER_H
#define AEDI_INTERPRETER_H

#include "database.h"

namespace AEDI {
namespace interpreter {

extern Database global_db;

void process_mcuac();
void process_pcuac();
void process_last();
void process_follow();
void process_date();
void process_tag();
bool read_command();

}  // namespace interpreter
}  // namespace AEDI

#endif
