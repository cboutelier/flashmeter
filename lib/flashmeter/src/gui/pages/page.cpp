#include "page.h"

Page::Page(DisplayDevice* d, Model *model,  ConsoleDelegator* console, char const *code){
   this->display = d;
   this->code = code;
   this->console = console;
   this->model = model;
   
}

Page::~Page(){
}


void Page::show(){
    console->println("Show of page");
}
