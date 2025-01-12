window.onload = () => {
  const obj = document.getElementById('obj');
  const github = document.getElementById('github');

  const text = ['(A)IoT Engineering', 'Web Development', "'safe' C++"];

  let i = 0;
  setInterval(() => {
    obj.innerText = ' ' + text[i];
    i = (i+1) % text.length
  }, 2000);


  github.addEventListener('click', (e) => {
    window.location.href = "https://github.com/Berigoo";
  });
}
