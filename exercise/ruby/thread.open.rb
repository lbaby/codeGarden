def readfiles(filenames)
threads = filenames.map { |f|
  Thread.new { File.read(f) }
  }
  threads.map { |t| t.value}
end

p readfiles(%w[a b c ])
