
import json
import os


mpi_typenames = [
    'MPI_Aint',
    'MPI_Comm',
    'MPI_Comm_copy_attr_function',
    'MPI_Comm_delete_attr_function',
    #'MPI_Comm_errhandler_function',
    'MPI_Datarep_conversion_function',
    'MPI_Datarep_extent_function',
    'MPI_Datatype',
    'MPI_Errhandler',
    'MPI_File',
    #'MPI_File_errhandler_function',
    'MPI_Grequest_cancel_function',
    'MPI_Grequest_free_function',
    'MPI_Grequest_query_function',
    'MPI_Group',
    'MPI_Info',
    'MPI_Offset',
    'MPI_Op',
    'MPI_Request',
    'MPI_Status',
    'MPI_Type_copy_attr_function',
    'MPI_Type_delete_attr_function',
    'MPI_User_function',
    'MPI_Win',
    'MPI_Win_copy_attr_function',
    'MPI_Win_delete_attr_function', ]
    #'MPI_Win_errhandler_function' ]

mpi_datatypes = [
    'MPI_CHAR',
    'MPI_BYTE',
    'MPI_SHORT',
    'MPI_INT',
    'MPI_LONG',
    'MPI_FLOAT',
    'MPI_DOUBLE',
    'MPI_UNSIGNED_CHAR',
    'MPI_UNSIGNED_SHORT',
    'MPI_UNSIGNED',
    'MPI_UNSIGNED_LONG',
    'MPI_LONG_DOUBLE',
    'MPI_LONG_LONG_INT',
    'MPI_FLOAT_INT',
    'MPI_LONG_INT',
    'MPI_DOUBLE_INT',
    'MPI_SHORT_INT',
    'MPI_2INT',
    'MPI_LONG_DOUBLE_INT',
    'MPI_PACKED',
    'MPI_UB',
    'MPI_LB' ]

mpi_misc = [
    'MPI_ANY_SOURCE',
    'MPI_PROC_NULL',
    'MPI_ROOT',
    'MPI_ANY_TAG',
    'MPI_MAX_PROCESSOR_NAME',
    'MPI_MAX_ERROR_STRING',
    'MPI_MAX_OBJECT_NAME',
    'MPI_UNDEFINED',
    'MPI_CART',
    'MPI_GRAPH',
    'MPI_KEYVAL_INVALID',
]

mpi_skipfuncs = ['MPI_Pcontrol',
                 'MPI_Op_commutative',
                 'MPI_Reduce_local']

mpi_byhandfuncs = ['MPI_Init']

mpi_skiptypes = ['MPI_Comm_errhandler_function*',
                 'MPI_File_errhandler_function*',
                 'MPI_Win_errhandler_function*',
                 'int**',
                 'char**',
                 'char***']

mpi_nullobj = {'MPI_Comm': {'NULL': 'MPI_COMM_NULL'},
               'MPI_Op': {'NULL': 'MPI_OP_NULL'},
               'MPI_Group': {'NULL': 'MPI_GROUP_NULL'},
               'MPI_Datatype': {'NULL': 'MPI_DATATYPE_NULL'},
               'MPI_Request': {'NULL': 'MPI_REQUEST_NULL'},
               'MPI_Status': {'NULL': 'NULL'},
               'MPI_Errhandler': {'NULL': 'MPI_ERRHANDLER_NULL'}}


mptr = "%(dt)s %(vn)s = (%(dt)s) luaL_checkudata(L, %(num)d, \"MPI::%(short)s\");"
mnop = "%(dt)s %(vn)s = *((%(dt)s*) luaL_checkudata(L, %(num)d, \"MPI::%(short)s\"));"
#void = "%(dt)s %(vn)s = lua_touserdata(L, %(num)d); luaL_checktype(L, %(num)d, LUA_TUSERDATA);"
void = "char *_type%(num)d = luaT_typename(L,%(num)d); MPI_THStorage *_storage%(num)d = luaT_toudata(L,%(num)d,_type%(num)d); %(dt)s %(vn)s = (void*) _storage%(num)d->data;"
#char = "%(dt)s %(vn)s = (char*) lua_touserdata(L, %(num)d); luaL_checktype(L, %(num)d, LUA_TUSERDATA);"
char = "char *_type%(num)d = luaT_typename(L,%(num)d); MPI_THStorage *_storage%(num)d = luaT_toudata(L,%(num)d,_type%(num)d); %(dt)s %(vn)s = (char*) _storage%(num)d->data;"
intv = "%(dt)s %(vn)s = luaL_checkint(L, %(num)d);"
#intp = "%(dt)s %(vn)s = (int*) lua_touserdata(L, %(num)d); luaL_checktype(L, %(num)d, LUA_TUSERDATA);"
intp = "char *_type%(num)d = luaT_typename(L,%(num)d); MPI_THStorage *_storage%(num)d = luaT_toudata(L,%(num)d,_type%(num)d); %(dt)s %(vn)s = (int*) _storage%(num)d->data;"

def lua_checkarg(dt, vn, num):
    """ tn: type declaration, vn: variable name, num: arg number """
    if dt.startswith('MPI_'):
        short = dt.replace('MPI_', '').replace('*', '')
        if '*' in dt:
            return  mptr % {'dt': dt, 'vn': vn, 'num': num, 'short': short }
        else:
            return  mnop % {'dt': dt, 'vn': vn, 'num': num, 'short': short }
    elif dt == 'void*':
        return void % {'dt': dt, 'vn': vn, 'num': num }
    elif dt == 'char*':
        return char % {'dt': dt, 'vn': vn, 'num': num }
    elif dt == 'int*':
        return intp % {'dt': dt, 'vn': vn, 'num': num }
    elif dt == 'int':
        return intv % {'dt': dt, 'vn': vn, 'num': num }
    elif dt == 'longv':
        return longv % {'dt': dt, 'vn': vn, 'num': num }
    else:
        raise RuntimeError("should never happen:")


class LuaFunction(object):
    def __init__(self, spec):
        self.arg_names = [a['name'] for a in spec['args']]
        self.arg_types = [a['type'] for a in spec['args']]
        self.func_name = spec['name']
        self.ret_type = spec['retVal']
        if self.ret_type not in ['int', 'double']:
            raise ValueError("return type no int or double")

    def write(self):
        lua_args = [ ]
        c_args = [ ]
        arg_num = 1
        for t, n in zip(self.arg_types, self.arg_names):
            if t in mpi_skiptypes:
                raise ValueError("function contains a skipped type")
            ca = lua_checkarg(t, n, arg_num)
            lua_args.append(ca)
            c_args.append(n)
            arg_num += 1

        func = (
            """static int _%(func_name)s(lua_State *L)
{
  %(lua_args)s
  %(ret_type)s res = %(func_name)s(%(c_args)s);
  lua_pushnumber(L, res);
  return 1;
}""" % { 'func_name': self.func_name,
         'lua_args': '\n  '.join(lua_args) if lua_args else "// no Lua args",
         'ret_type': self.ret_type,
         'c_args': ', '.join(c_args)})
        return func


all_types = set()
wrapped_funcs = [ ]

luampi_funcs = [ ]
specs = os.listdir('specs')
specs.sort()
for spec in specs:
    func = LuaFunction(json.load(open('specs/' + spec)))
    if func.func_name in mpi_skipfuncs: continue
    luampi_funcs.append(func)
    for tname in func.arg_types:
        all_types.add(tname)

for func in luampi_funcs:
    try:
        print func.write()
        wrapped_funcs.append(func.func_name)
    except ValueError as e:
        pass #print e

print "luaL_Reg MPI_module_funcs[] = {"
for func in wrapped_funcs + mpi_byhandfuncs:
    print "  { \"%s\", _%s}," % (func.replace('MPI_', ''), func)
print "  {NULL, NULL}};"



