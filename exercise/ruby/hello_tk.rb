#!/usr/bin/env ruby

require 'tk'
hello = TkRoot.new
TkLabel.new( hello ) do
    text "\n  Hello, Matz!  \n"
        pack
        end
Tk.mainloop
