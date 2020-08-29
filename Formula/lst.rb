class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.1.1-alpha.tar.gz"
  license "GNU GPL v3"
  version "1.1.0"

  def install
    bin.install "lst"
  end

end
