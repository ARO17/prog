d=document.body;
b=c=i=d.style.margin=0;
_=d.children[0];
j=_.width=innerWidth/3;
k=_.height=innerHeight/3;
N=_.style;N.height=N.width="100%";
M=Math;
D=[];
H=[];
P=4e3;
O=2e4;
r=M.random;
with(C=_.getContext("2d")){font="24px Arial";fillText("js1k",0,20);d=getImageData(0,0,e=45,f=25);while(i<P)a=r()*2-1,g=M.pow(a*a+b*b+c*c,.5)/2,D[i]=[a/g,b/g+1,c/g],c=b,b=a,x=r()*e,y=r()*f,d.data[((y|0)*e+(x|0))*4+3]>9?H[i++]=[(x-e/2)/f*2.5,(.5-y/f)*2.5,r()/2]  ;v=createRadialGradient(j/2,k*2/3,0,j/2,k,k/2)}v[a='addColorStop'](0,"#343");v[a](1,"#000");C[J='fillStyle']=v;C[F='fillRect'](0,0,j,k);function n(i){return(w[i]-b[i])*M.pow(m,5)+b[i]}function X(){g=new Date%O/O*4;C[F](0,0,j,k);e=M.cos(a=g*M.PI*2);f=M.sin(a);for(i=0;i<P;b=H[i++])w=D[i],m=g>=3?0:g>=2?1-g%1:g>=1?1:g%1,d=n(2),h=n(1),l=n(0),c=1/(f*l-e*d-4)*k,a=[(c*(e*l+f*d)+j)/2,((i%2?c*(-h-2  c*h)+k)/2],C[J]=i%2?"#373":"#0f0",C[F](a[0]|0,a[1]|0,.9,.9);C[B='drawImage'](_,0,0,L=35,K=35);C[u='globalAlpha']=.6;C[B](_,0,0,L,K,0,0,j,k);C[u]=1;C[J]=v;C[F](0,0,L,K);setTimeout(X,9)}X()
