#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int l_sin(lua_State *L)
{
	double d = luaL_checknumber(L,1);
	lua_pushnumber(L,sin(d));
	return 1;
}

static int l_dir(lua_State *L)
{
	DIR *dir;
	struct dirent *entry;
	int i;
	const char *path = luaL_checkstring(L,1);
	dir = opendir(path);
	if (dir == NULL) 
	{
		lua_pushnil(L);
		lua_pushstring(L,strerror(errno));	
		return 2;
	}

	lua_newtable(L);
	i = 1;
	while((entry = readir(dir)) != NULL)
	{
		lua_pushnumber(L,i++);
		lua_pushstring(L,entry->d_name);
		lua_settable(L,-3);
	}
	closedir(dir);
	return 1;
}

int main(void)
{
	lua_State *l = lua_open();
	
	lua_pushcfunction(l,l_sin);
	lua_setglobal(l,"mysin");

	lua_pushcfunction(l,l_dir);
	lua_setglobal(l,"mydir");
	
	return 0;
}