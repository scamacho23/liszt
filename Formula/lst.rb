class Lst < Formula
  desc "Save snippets of information quickly through the command line"
  homepage "https://liszt.readthedocs.io"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.1.7-alpha.tar.gz"
  sha256 "30c9464e80e0b191a58471c0bd10ec6a054ae4fe668e61d1544302266b702af8"
  license "GNU GPL-3.0"
  version "1.1.7-alpha"

  depends_on "cmake" => :build

  def install
    system "cmake", ".", *std_cmake_args
    system "make"
    bin.install "lst"
  end

  test do
    system "lst " "-ch " "default"
    expected = <<~EOS
	default
    EOS

    assert_match expected, shell_output("#{bin}/lst -n")
  end
end
