class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.0.18.tar.gz"
  sha256 "3f23d61a0f2fb49540ff284e426d7ab2deec3b56103e2bec8a901a37ef232481"
  license "GNU GPL v3"
  version "1.0.19"

  bottle do
    sha256 "4053e304e58e0306bbcda36aa0475676b797d8fafbcb811dab79db3e763e3fc8" => :catalina  
  end

  def install
    bin.install "lst"
  end

end
