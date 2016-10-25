#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.


if WinExist("ahk_class MozillaWindowClass") {
    SetTitleMatchMode, 1
    WinWaitActive, ahk_class MozillaWindowClass
    WinGet, tb_id, ID, A
    WinGetTitle, tb_title, ahk_id %tb_id%
    While InStr(tb_title, "Access Denied") <> 0 Or InStr(tb_title, "Forbidden") <> 0 {
        WinWaitActive, ahk_id %tb_id%
        SendInput {Ctrl down}{Shift down}L{Shift up}{Ctrl up}
        Sleep, 5000
        WinGetTitle, tb_title, ahk_id %tb_id%
    }
}
