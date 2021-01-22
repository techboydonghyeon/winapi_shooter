#pragma once


#define SAFE_DELETE(name) if(name) {delete name; name = nullptr;}
#define SAFE_DELETE_ARRAY(name) if(name){for(UINT i =0; i< name.size(); ++i){delete name[i]; name[i] = nullptr;}}
