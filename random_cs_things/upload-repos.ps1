$repos = "algorithms-project-laboratory",
"computer-architecture-iii",
"database",
"dev-lab-for-mobile-devices",
"graphs",
"lab-of-computer-architecture",
"skill-challenges",
"software-engineering-i"

$repos | ForEach-Object {
    Push-Location "$_"
    git config user.name axell-brendow
    git config user.email breno.axel@gmail.com
    git pull
    git add *
    git commit -m "First upload"
    git push
    Pop-Location
}
