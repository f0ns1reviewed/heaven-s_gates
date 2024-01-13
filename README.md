# Heaven's gates!

```
She said to me, I'll take you to the heaven's gates ! 
```

## Compile
```
@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tp *.cpp /link /OUT:heavens_gates.exe /SUBSYSTEM:CONSOLE 

del *.obj
```
