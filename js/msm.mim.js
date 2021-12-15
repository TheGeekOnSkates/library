function msmCreate(l){var n=document.createElement('nav'),b=document.createElement('button'),m=document.createElement('div');n.setAttribute('role','navigation');n.className='msm-nav';b.className='msm-btn';b.innerHTML='&#9776;';b.setAttribute('aria-label','menu');b.setAttribute('aria-expanded','false');b.onclick=_msmOnExpand;m.className='msm-menu';m.style.display='none';m.setAttribute('role','menu');for(var i=0;i<l.length;i++){var mi=document.createElement('button');mi.setAttribute('role','menuitem');mi.className='msm-menuitem';mi.innerText=l[i].label;if(l[i].url){mi.setAttribute('data-url',l[i].url);mi.onclick=_msmOnLink}
else mi.onclick=l[i].code;m.appendChild(mi);}
n.appendChild(b);n.appendChild(m);return n;}
function _msmOnExpand(e){if(e.target.getAttribute('aria-expanded')=='true'){e.target.innerHTML='&#9776;';e.target.setAttribute('aria-expanded','false');e.target.nextElementSibling.style.display='none';return;}
e.target.innerHTML='&#x00D7';e.target.setAttribute('aria-expanded','true');e.target.nextElementSibling.style.display='';}
function _msmOnLink(e){window.location=e.target.getAttribute('data-url');}
