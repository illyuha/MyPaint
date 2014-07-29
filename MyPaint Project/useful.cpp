#include "useful.h"
#include <cmath>


int SDL_RenderDrawEllipse(SDL_Renderer * renderer, const SDL_Rect * rect, int width)
{
	// implementation of the midpoint algorithm
	// useful links: 
	// http://geofhagopian.net/sablog/Slog-october/sablog-10-24-05.htm 
	// http://winnyefanho.net/research/MEA.pdf

	double a = 0.5 * rect->w, b = 0.5 * rect->h;
	double asq = a * a, bsq = b * b;
	double x0 = 0, y0 = b;
	double xstop = asq / sqrt(asq+bsq);
	double p0 = bsq - asq * b + 0.25 * asq;
	
	double x = x0, y = y0, p = p0;
	
	for (int i = 0; i < width; ++i)
	{
		SDL_RenderDrawPoint(renderer,rect->x+a+x,rect->y+b-y+i);
		SDL_RenderDrawPoint(renderer,rect->x+a+x,rect->y+b+y-i);
	}

	// drawing dots in the first region

	while (x < xstop)
	{
		++x;
		if (p < 0)
		{
			p += 2.0 * bsq * x + bsq;
		}
		else
		{
			--y;
			p += 2.0 * bsq * x + bsq - 2.0 * asq * y;
		}
		for (int i = 0; i < min(int(y+1),width); ++i)
		{
			SDL_RenderDrawPoint(renderer,rect->x+a+x,rect->y+b-y+i);
			SDL_RenderDrawPoint(renderer,rect->x+a-x,rect->y+b-y+i);
			SDL_RenderDrawPoint(renderer,rect->x+a+x,rect->y+b+y-i);
			SDL_RenderDrawPoint(renderer,rect->x+a-x,rect->y+b+y-i);
		}
	}

	x0 = xstop;
	y0 = bsq / sqrt(asq+bsq);
	
	// drawing dots in the second region

	for (double x = x0, y = y0; y > 0; )
	{
		--y;
		if (p > 0)
		{
			p += asq * (1.0 - 2.0 * y);
		}
		else
		{
			++x;
			p += asq * (1.0 - 2.0 * y) + 2.0 * bsq * x;
		}
		for (int i = 0; i < min(int(x+1),width); ++i)
		{
			SDL_RenderDrawPoint(renderer,rect->x+a+x-i,rect->y+b-y);
			SDL_RenderDrawPoint(renderer,rect->x+a-x+i,rect->y+b-y);
			SDL_RenderDrawPoint(renderer,rect->x+a+x-i,rect->y+b+y);
			SDL_RenderDrawPoint(renderer,rect->x+a-x+i,rect->y+b+y);
		}
	}

	return 0;
}

int SDL_RenderDrawLine(SDL_Renderer * renderer, int x1, int y1, int x2, int y2, int brushWidth)
{
	double fx = x1, fy = y1, sx = x2, sy = y2;

	double height = sy - fy, width = fabs(sx-fx);
	double lineLength = sqrt(height*height+width*width);

	// alpha is an angle between the line and Oy
	double cosAlpha = (lineLength == 0) ? 0 : height / lineLength, sinAlpha = sqrt(1-cosAlpha*cosAlpha);
	static const double STEP = 0.1;

	int px1 = 0, py1 = 0, px2 = 0, py2 = 0;
	for (double w = -0.5 * brushWidth; w < 0.5 * brushWidth; w += STEP)
	{
		double dx = w * cosAlpha, dy = w * sinAlpha;
		if (fx < sx)
		{
			int x1 = fx+dx, y1 = fy-dy, x2 = sx+dx, y2 = sy-dy;
			if (!(px1 == x1 && py1 == y1 && px2 == x2 && py2 == y2))
			{
				SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
				if (px1 != 0 && !(x1 == x2 || y1 == y2))
					SDL_RenderDrawLine(renderer,max(x1,px1),max(y1,py1),min(x2,px2),min(y2,py2));
				px1 = x1, py1 = y1, px2 = x2, py2 = y2;
			}
		}
		else
		{
			int x1 = fx+dx, y1 = fy+dy, x2 = sx+dx, y2 = sy+dy;
			if (!(px1 == x1 && py1 == y1 && px2 == x2 && py2 == y2))
			{
				SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
				if (px1 != 0 && !(x1 == x2 || y1 == y2))
					SDL_RenderDrawLine(renderer,min(x1,px1),max(y1,py1),max(x2,px2),min(y2,py2));
				px1 = x1, py1 = y1, px2 = x2, py2 = y2;
			}
		}
	}
	return 0;
}

int SDL_RenderDrawRect(SDL_Renderer * renderer, const SDL_Rect * rect, int width)
{
	SDL_Rect r = *rect;
	do
	{
		SDL_RenderDrawRect(renderer,&r);

		r.h -= 2;
		r.w -= 2;
		++r.x;
		++r.y;
		--width;
	}
	while (width > 0 && min(r.h,r.w) > 0);
	return 0;
}
