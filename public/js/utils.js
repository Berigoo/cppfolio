
/**
 *@param e {HTMLElement}
 */
function collapseHeader(e) {
  const animDuration = 0.5;

  const headingParent = e.parentElement.parentElement;
  const headingChildren = e.parentElement.nextElementSibling;

  if (!headingParent.classList.contains("is-animating")) {
    const t = headingParent.classList.contains("is-collapsed");

    setTimeout(() => {
      headingParent.classList.toggle("is-animating");
      headingParent.classList.toggle("is-collapsed", !t);
      headingChildren.style = "";
      (t) ? (null) : (headingChildren.style.height = "0px");
    }, animDuration * 1000);

    headingParent.classList.toggle("is-animating", true);
    headingParent.classList.toggle("is-collapsed", !t)
    headingChildren.style.transitionDuration = animDuration + "s";
    (t) ? (headingChildren.style.height = "auto") : (headingChildren.style.height = "0px");
  }
}

function initGlobals() {
}

function initialize() {
  const collapser = document.getElementsByClassName("heading-collapse-indicator");
  for (let index = 0; index < collapser.length; index++) {
    const element = collapser[index];
    element.onclick = () => collapseHeader(element);
  };
}

window.onload = function() {
  initGlobals();
  initialize();
}
