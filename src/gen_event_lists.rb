#!/usr/bin/ruby -w

def gen_event_list(regex, outfilename)
  File.open(outfilename, 'w') do |fout|
    fout.puts("// autogenerated by gen_event_list.rb, do not edit by hand\n")
    fout.puts
    File.new("/usr/include/linux/input.h").grep(regex).each do |i|
      name = i.split[1];
      if not name =~ /_MAX$/ and not name =~ /_CNT$/
        fout.puts "#ifdef #{name}"
        fout.puts "  add(%s, \"%s\");" % [name, name]
        fout.puts "#endif"
        fout.puts
      end
    end
    fout.puts "/* EOF */"
  end
end

gen_event_list(/^#define (BTN|KEY)/, 'key_list.x')
gen_event_list(/^#define REL/,       'rel_list.x')
gen_event_list(/^#define ABS/,       'abs_list.x')

# EOF #
