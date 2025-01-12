window.onload = () => {
  const obj = document.getElementById('obj');

  const text = ['(A)IoT Engineering', 'Web Development', "'safe' C++"];

  let i = 0;
  setInterval(() => {
    obj.innerText = ' ' + text[i];
    i = (i+1) % text.length
  }, 2000);
}
