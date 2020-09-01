class Lst < Formula
  desc "Save snippets of information quickly through the command line"
  homepage "https://liszt.readthedocs.io"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.1.7-alpha.tar.gz"
  license "GNU GPL-3.0"
  version "1.1.7-alpha"

  depends_on "cmake" => :build

  def install
    system "cmake", ".", *std_cmake_args
    system "make"
    bin.install "lst"
  end

  test do
    system "lst"
    expected = <<~EOS
	"\033[1m-l\033[0m \033[1m\033[34m==>\033[0m for \033[1mlisting \033[0mmemories on the current note\n"
	"     Usage: 'lst -l'\n"
    EOS

    assert_match expected, shell_output("#{bin}/lst -h -l")
  end
end
