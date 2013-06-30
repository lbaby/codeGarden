# This module provides constants that define the UTF-8 strings for
# all Unicode codepoints. It uses const_missing to define them lazily.
# Examples:
#   copyright = Unicode::U00A9
#   euro = Unicode::U20AC
#   infinity = Unicode::U221E
module Unicode
  # This method allows us to define Unicode codepoint constants lazily.
  def self.const_missing(name)  # Undefined constant passed as a symbol
    # Check that the constant name is of the right form.
    # Capital U followed by a hex number between 0000 and 10FFFF.
    if name.to_s =~ /^U([0-9a-fA-F]{4,5}|10[0-9a-fA-F]{4})$/
      # $1 is the matched hexadecimal number. Convert to an integer.
      codepoint = $1.to_i(16)
      # Convert the number to a UTF-8 string with the magic of Array.pack.
      utf8 = [codepoint].pack("U")
      # Make the UTF-8 string immutable.
      utf8.freeze
      # Define a real constant for faster lookup next time, and return
      # the UTF-8 text for this time.
      const_set(name, utf8)
    else 
      # Raise an error for constants of the wrong form.
      raise NameError, "Uninitialized constant: Unicode::#{name}"
    end
  end
end
