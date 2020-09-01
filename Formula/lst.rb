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
      "\e[1mLiszt v1.1.7-alpha\e[0m\n"
    EOS

    assert_match expected, shell_output("#{bin}/lst -h -l")
  end
end
