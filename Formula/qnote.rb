class Qnote < Formula
	desc "A command line note-taking software"
	homepage "https://github.com/scamacho23/quicknote"
	url "https://github.com/scamacho23/homebrew-quicknote/blob/master/qnote-v1.0.6.tar.xz"
	sha256 "21d250f46775d9c966d6841949e8e3b28023710e1f14d82c3cbd8028d29cddc2"
	version "1.0.6"

	depends_on "python3"
	
	bottle :unneeded

	def install
		bin.install "qnote"
		echo "Hello, World"
	end
end
