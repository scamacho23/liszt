class Qnote < Formula
	desc "A command line note-taking software"
	homepage "https://github.com/scamacho23/quicknote"
	url "https://github.com/scamacho23/quicknote/blob/master/archive.tar.gz"
	sha256 "9252d4e8c71a50cd37c1ad34c9d48b504f25ba2c7e0f928ac1d5125724fa3320"
	version "1.0.6"

	depends_on "python3"
	
	bottle :unneeded

	def install
		bin.install "qnote"
	end
end
