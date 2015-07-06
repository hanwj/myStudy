#include <stdio.h>
#include <stdarg.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void error(lua_State *L,const char *fmt,...)
{
	va_list argp;
	va_start(argp,fmt);
	vfprintf(stderr,fmt,argp);
	va_end(argp);
}

void call_va(lua_State* L,const char* func,const char* sig,...)
{
	va_list vl;
	int narg,nres;

	va_start(vl,sig);
	lua_getglobal(L,func);

	narg = 0;
	while(*sig)
	{
		switch(*sig++)
		{
			case 'd':
				lua_pushnumber(L,va_arg(vl,double));
				break;
			case 'i':
				lua_pushnumber(L,va_arg(vl,int));
				break;
			case 's':
				lua_pushstring(L,va_arg(vl,char*));
				break;
			case '>':
				goto endwhile;
			default:
				error(L,"invalid option (%c)",*(sig-1));
		}
		narg++;
		luaL_checkstack(L,1,"too many arguments");
	}
	endwhile:

	nres = strlen(sig);
	if(lua_pcall(L,narg,nres,0) != 0)
	{
		error(L,"error running function '%s' : %s",func,lua_tostring(L,-1));
	}

	nres = -nres;
	while(*sig)
	{
		swith(*sig++)
		{
			case 'd':
				if (!lua_isnumber(L,nres))
				{
					error(L,"wrong result type");
				}
				*va_arg(vl,double*) = lua_tonumber(L,nres);
				break;
			case 'i':
				if(!lua_isnumber(L,nres))
				{
					error(L,"wrong result type");
				}
				*va_arg(vl,int*) = lua_tonumber(L,nres);
				break;
			case 's':
				if(!lua_isstring(L,nres))
				{
					error(L,"wrong result type");
				}
				*va_arg(vl,const char **) = lua_tostring(L,nres);
				break;
			default:
				error(L,"invalid option (%c)",*(sig-1));	
		}
		nres++;
	}
	va_end(vl);
}

int main(void)
{
	return 0;
}