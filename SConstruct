import excons
import excons.tools.python
import os
import subprocess
import pprint


swigexe = os.path.abspath("SWIG/swig.exe").replace("\\", "/")
swiglib = os.path.abspath("SWIG/swig_lib").replace("\\", "/")

swig_interface_parents = {
   # source file base,     "base class" for generated COM support
   'mapi':                 None, # not a class, but module
   'PyIMailUser':          'IMAPIContainer',
   'PyIABContainer':       'IMAPIContainer',
   'PyIAddrBook':          'IMAPIProp',
   'PyIAttach':            'IMAPIProp',
   'PyIDistList':          'IMAPIContainer',
   'PyIMailUser':          'IMAPIContainer',
   'PyIMAPIContainer':     'IMAPIProp',
   'PyIMAPIFolder':        'IMAPIContainer',
   'PyIMAPIProp':          '', # '' == default base
   'PyIMAPISession':       '',
   'PyIMAPIStatus':        'IMAPIProp',
   'PyIMAPITable':         '',
   'PyIMessage':           'IMAPIProp',
   'PyIMsgServiceAdmin':   '',
   'PyIProviderAdmin':     '',
   'PyIMsgStore':          'IMAPIProp',
   'PyIProfAdmin':         '',
   'PyIProfSect':          'IMAPIProp',
   'PyIConverterSession':  '',
   # exchange and exchdapi
   'exchange':             None,
   'exchdapi':             None,
   'PyIExchangeManageStore': '',
   'PyIExchangeManageStoreEx': '',
   # ADSI
   'adsi':                 None, # module
   'PyIADsContainer':      'IDispatch',
   'PyIADsDeleteOps':      'IDispatch',
   'PyIADsUser':           'IADs',
   'PyIDirectoryObject':   '',
   'PyIDirectorySearch':   '',
   'PyIDsObjectPicker':    '',
   'PyIADs':               'IDispatch'
}

def swig(target, source, env):
   lst = [swigexe, "-python", "-c++"]
   if float(excons.tools.python.Version()) < 3.0:
      lst.append("-DSWIG_PY2K")
   lst.append("-DSWIG_PY64BIT")
   lst.append("-I%s" % swiglib)
   lst.append("-I%s/python" % swiglib)
   lst.append("-dnone")
   try:
      interface_parent = swig_interface_parents[os.path.basename(os.path.splitext(str(source[0]))[0])]
   except KeyError:
      pass
   else:
      # Using win32 extensions to SWIG for generating COM classes.
      if interface_parent is not None:
         # generating a class, not a module.
         lst.append("-pythoncom")
         if interface_parent:
            # A class deriving from other than the default
            lst.extend(["-com_interface_parent", interface_parent])
   lst.extend(["-o", str(target[0]), str(source[0])])
   cmd = subprocess.list2cmdline(lst)
   print(cmd)
   subprocess.Popen(cmd, env=env["ENV"], shell=True).communicate()

def makerc(target, source, env):
   dn = os.path.dirname(str(target[0]))
   bn = os.path.splitext(os.path.basename(str(target[0])))[0]
   lst = ["mc", "-h", dn, "-r", dn, "-z", bn]
   lst.extend(map(str, source))
   cmd = subprocess.list2cmdline(lst)
   print(cmd)
   subprocess.Popen(cmd, env=env["ENV"], shell=True).communicate()

def makeres(target, source, env):
   lst = ["rc", "/fo", str(target[0]), str(source[0])]
   cmd = subprocess.list2cmdline(lst)
   print(cmd)
   subprocess.Popen(cmd, env=env["ENV"], shell=True).communicate()


env = excons.MakeBaseEnv()

env.Append(BUILDERS={"MakeRC": Builder(action=makerc, suffix='.rc', src_suffix='.mc'),
                     "MakeRES": Builder(action=makeres, suffix='.res', src_suffix='.rc'),
                     "Swig": Builder(action=swig, suffix='.cpp', src_suffix='.i')})

env.Append(CCFLAGS=["/wd4701",
                    "/wd4703",
                    "/wd4706",
                    "/wd4100",
                    "/wd4244",
                    "/wd4211",
                    "/wd4189",
                    "/wd4477",
                    "/wd4267",
                    "/wd4838",
                    "/wd4505",
                    "/wd4005",
                    "/wd4456",
                    "/wd4702"])

pm_rc = env.MakeRC("win32/src/PerfMon/PyPerfMsgs.rc", ["win32/src/PerfMon/PyPerfMsgs.mc"])
pm_res = env.MakeRES("win32/src/PerfMon/PyPerfMsgs.res", pm_rc)
w32s_rc = env.MakeRC("win32/src/win32service_messages.rc", ["win32/src/win32service_messages.mc"])
w32s_res = env.MakeRES("win32/src/win32service_messages.res", ["win32/src/win32service_messages.rc"])

pylibdir = excons.OutputBaseDirectory() + "/lib/" + excons.tools.python.Version()

prjs = [
   {
      "name": "pywintypes",
      "type": "sharedlib",
      "prefix": excons.tools.python.Version(),
      "bldprefix": "py-%s" % excons.tools.python.Version(),
      "defs": ["BUILD_PYWINTYPES"],
      "libs": ["advapi32", "user32", "ole32", "oleaut32"],
      "srcs": ["win32/src/PyACL.cpp",
               "win32/src/PyDEVMODE.cpp",
               "win32/src/PyHANDLE.cpp",
               "win32/src/PyIID.cpp",
               "win32/src/PyLARGE_INTEGER.cpp",
               "win32/src/PyOVERLAPPED.cpp",
               "win32/src/PySECURITY_ATTRIBUTES.cpp",
               "win32/src/PySECURITY_DESCRIPTOR.cpp",
               "win32/src/PySID.cpp",
               "win32/src/PyTime.cpp",
               "win32/src/PyUnicode.cpp",
               "win32/src/PyWAVEFORMATEX.cpp",
               "win32/src/PyWinTypesmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   }, 
   {
      "name": "perfmondata",
      "type": "sharedlib",
      "prefix": excons.tools.python.Version(),
      "bldprefix": "py-%s" % excons.tools.python.Version(),
      "defs": ["UNICODE", "_UNICODE"],
      "libs": ["advapi32"] + pm_res,
      "deps": pm_rc + pm_res,
      "srcs": ["win32/src/PerfMon/perfmondata.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "mmapfile",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "libs": [],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/mmapfilemodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "odbc",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "libs": ["odbc32", "odbccp32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/odbc.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "perfmon",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "incdirs": ["win32/src"],
      "libs": [],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/PerfMon/MappingManager.cpp",
               "win32/src/PerfMon/PerfCounterDefn.cpp",
               "win32/src/PerfMon/PerfObjectType.cpp",
               "win32/src/PerfMon/PyPerfMon.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "timer",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "libs": ["user32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/timermodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win2kras",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "libs": ["rasapi32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win2krasmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32cred",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "libs": ["advapi32", "credui"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32credmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32crypt",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "incdirs": ["win32/src"],
      "libs": ["advapi32", "crypt32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32crypt/win32cryptmodule.cpp",
               "win32/src/win32crypt/win32crypt_structs.cpp",
               "win32/src/win32crypt/PyCERTSTORE.cpp",
               "win32/src/win32crypt/PyCERT_CONTEXT.cpp",
               "win32/src/win32crypt/PyCRYPTHASH.cpp",
               "win32/src/win32crypt/PyCRYPTKEY.cpp",
               "win32/src/win32crypt/PyCRYPTMSG.cpp",
               "win32/src/win32crypt/PyCRYPTPROV.cpp",
               "win32/src/win32crypt/PyCTL_CONTEXT.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32file",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["__WIN32__"],
      "libs": [],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32file_comm.cpp"] +
              env.Swig("win32/src/win32file.cpp", ["win32/src/win32file.i"]),
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32event",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["__WIN32__"],
      "libs": ["user32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": env.Swig("win32/src/win32event.cpp", ["win32/src/win32event.i"]),
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32clipboard",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "libs": ["gdi32", "user32", "shell32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32clipboardmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32job",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["__WIN32__", "UNICODE", "_UNICODE"],
      "libs": ["user32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": env.Swig("win32/src/win32job.cpp", ["win32/src/win32job.i"]),
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32lz",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "libs": ["lz32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32lzmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32net",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "incdirs": ["win32/src"],
      "libs": ["netapi32", "advapi32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32net/win32netfile.cpp",
               "win32/src/win32net/win32netgroup.cpp",
               "win32/src/win32net/win32netmisc.cpp",
               "win32/src/win32net/win32netmodule.cpp",
               "win32/src/win32net/win32netsession.cpp",
               "win32/src/win32net/win32netuse.cpp",
               "win32/src/win32net/win32netuser.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32pdh",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "libs": [],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32pdhmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32pipe",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["__WIN32__"],
      "libs": [],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32popen.cpp"] +
              env.Swig("win32/src/win32pipe.cpp", ["win32/src/win32pipe.i"]),
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32print",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "incdirs": ["win32/src"],
      "libs": ["winspool", "user32", "gdi32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32print/win32print.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32process",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["__WIN32__"],
      "libs": ["advapi32", "user32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": env.Swig("win32/src/win32process.cpp", ["win32/src/win32process.i"]),
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32profile",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "incdirs": ["win32/src"],
      "libs": ["userenv"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32profilemodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32ras",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "incdirs": ["win32/src"],
      "libs": ["rasapi32", "user32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32rasmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32security",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["__WIN32__", "UNICODE", "_UNICODE"],
      "libs": ["advapi32", "user32", "netapi32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32security_sspi.cpp",
               "win32/src/win32security_ds.cpp"] +
              env.Swig("win32/src/win32security.cpp", ["win32/src/win32security.i"]),
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32service",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["__WIN32__", "UNICODE", "_UNICODE"],
      "libs": ["advapi32", "user32", "oleaut32"] + w32s_res,
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": env.Swig("win32/src/win32service.cpp", ["win32/src/win32service.i"]),
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32trace",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "incdirs": ["win32/src"],
      "libs": ["advapi32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32trace.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32wnet",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "incdirs": ["win32/src"],
      "libs": ["netapi32", "mpr"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32wnet/PyNCB.cpp",
               "win32/src/win32wnet/PyNetresource.cpp",
               "win32/src/win32wnet/win32wnet.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32inet",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["__WIN32__"],
      "libs": ["wininet"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32inet_winhttp.cpp"] + 
              env.Swig("win32/src/win32inet.cpp", ["win32/src/win32inet.i"]),
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32console",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "incdirs": ["win32/src"],
      "libs": ["kernel32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32consolemodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32ts",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "incdirs": ["win32/src"],
      "libs": ["wtsapi32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32tsmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "_win32sysloader",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": [],
      "incdirs": ["win32/src"],
      "libs": [],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/_win32sysloader.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   {
      "name": "win32transaction",
      "type": "dynamicmodule",
      "ext": excons.tools.python.ModuleExtension(),
      "prefix": excons.tools.python.ModulePrefix() + excons.tools.python.Version() + "/win32",
      "defs": ["UNICODE", "_UNICODE"],
      "incdirs": ["win32/src"],
      "libs": ["kernel32"],
      "deps": [],
      "libdirs": [pylibdir],
      "link": ["pywintypes"],
      "srcs": ["win32/src/win32transactionmodule.cpp"],
      "custom": [excons.tools.python.SoftRequire]
   },
   # win32 base modules
]

excons.DeclareTargets(env, prjs)