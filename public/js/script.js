window.onload = () => {
  const obj = document.getElementById('obj');
  const github = document.getElementById('github');
  const nav = document.getElementsByTagName('nav').item(0);
  const text = ['(A)IoT Engineering', 'Web Development', "Software Engineering"];

  let i = 1;
  obj.innerText = ' ' + text[0];
  setInterval(() => {
    obj.innerText = ' ' + text[i];
    i = (i+1) % text.length
  }, 2000);


  github.addEventListener('click', (e) => {
    window.location.href = "https://github.com/Berigoo";
  });
  github.addEventListener('pointerover', (e) => {
    github.style.cursor = "pointer";
  });

  for (let i = 0; i < nav.children.length; i++) {
    nav.children[i].addEventListener('pointerover', (e) => {
      nav.children[i].style.cursor = "pointer";
    });
  }
}
