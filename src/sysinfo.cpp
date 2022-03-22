/*
 * ========================================================================
 *
 *       Filename:  sysinfo.c
 *
 *    Description:  To extract the sysinfo from structure utsname
 *
 *        Version:  1.0
 *        Created:  30/04/20 23:12:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =======================================================================
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/xpm.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <sys/utsname.h>
#include <sys/stat.h>

#include <wchar.h>

#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/ioctl.h>


#include "common.h"

#ifdef _GCC_
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
#pragma GCC diagnostic ignored "-Wstringop-overflow="
#pragma GCC diagnostic ignored "-Wpointer-sign"
#endif

char mac[245] = {0};
char ipa[256] = {0};
char hst[256] = {0};

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int get_spen (XColor desired_col)
 *  Description:  
 * ===================================================================
 */
    int 
get_spen (Display *dpy, GC gc, XColor desired_col)
{   XSetForeground (dpy,
                    gc,
                    desired_col.pixel);
    return (0);
}		/* -----  end of function int get_spen (XColor desired_col)  ----- */
/* 
 * ===  FUNCTION  =======================================================
 *         Name:  get_macaddress
 *  Description:  
 * ======================================================================
 */
   void
get_mac_address ()
{
    struct ifaddrs *ifAddrStruct = NULL, *ifa = NULL;
    struct ifreq ifr;
    void * tmpAddrPtr = NULL;
    int n;
    char macbuf[20];
    
    if ((n = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror ("Socket error!"); exit (EXIT_FAILURE);
    }

    getifaddrs (&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
         char mask[INET_ADDRSTRLEN];
         void * mask_ptr = &((struct sockaddr_in*) 
                                ifa->ifa_netmask)->sin_addr;
         inet_ntop (AF_INET, mask_ptr, mask, INET_ADDRSTRLEN);
         if (strcmp(mask, "255.0.0.0") != 0)
         {
            tmpAddrPtr = &((struct sockaddr_in*) ifa->ifa_addr)->sin_addr;
            char addrbuf[INET_ADDRSTRLEN];
            inet_ntop (AF_INET, tmpAddrPtr, addrbuf, INET_ADDRSTRLEN);

            strcpy (ifr.ifr_name, ifa->ifa_name); //, strlen(ifa->ifa_name));
            if (ioctl (n, SIOCGIFHWADDR, &ifr) < 0)
            {
                perror ("ioctl error"); exit (EXIT_FAILURE);
            }
            unsigned char *hwaddr = (unsigned char *)
            ifr.ifr_hwaddr.sa_data;

           sprintf (macbuf,"%02X:%02X:%02X:%02X:%02X:%02X\n",
                  hwaddr[0],hwaddr[1],hwaddr[2],hwaddr[3],hwaddr[4],hwaddr[5]);
           strcpy (mac, macbuf);
           close(n);
           //out.macAddress.append (macbuf);
         } else if (ifa->ifa_addr->sa_family == AF_INET6) 
           {
                // DO SOMETHING HERE TO DISPLAY IPV6 DETAILS
            }
          }
    }
    if (ifAddrStruct != NULL) {
        freeifaddrs (ifAddrStruct); }
}

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  get_ipaddress
 *  Description:  
 * ======================================================================
 */
   void
get_ip_address ()
{
    struct ifaddrs *ifAddrStruct = NULL, *ifa = NULL;
    struct ifreq ifr;       // = {0};
    void * tmpAddrPtr = NULL;
    int n;
    char localip[2000]  = {0};
    
    if ((n = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror ("Socket error!"); exit (EXIT_FAILURE);
    }

    getifaddrs (&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
       if (ifa->ifa_addr->sa_family == AF_INET) {
        
            char mask[INET_ADDRSTRLEN];
            void *mask_ptr = &((struct sockaddr_in*) 
                    ifa->ifa_netmask)->sin_addr;

            inet_ntop (AF_INET, mask_ptr, mask, INET_ADDRSTRLEN);
            if (strcmp(mask, "255.0.0.0") != 0) {
                tmpAddrPtr = &((struct sockaddr_in*) 
                        ifa->ifa_addr)->sin_addr;

                char addrbuf[INET_ADDRSTRLEN];
                inet_ntop (AF_INET, tmpAddrPtr, addrbuf, INET_ADDRSTRLEN);
            
                sprintf (localip, "%s  %s\n",ifa->ifa_name, addrbuf);
                strcpy (ipa, localip);                
               close(n);
             } else if (ifa->ifa_addr->sa_family == AF_INET6) {
                 // DO SOMETHING HERE TO DISPLAY IPV6 DETAILS
                }
            }
        }
    if (ifAddrStruct != NULL) {
        freeifaddrs (ifAddrStruct);
    }    
}		/* -----  end of function get_ipaddress  ----- */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  get_hostname
 *  Description:  
 * ======================================================================
 */
    void
get_hostname ()
{   
    gethostname (hst, 24);
}		/* -----  end of function get_hostname  ----- */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  display_sysinfo
 *  Description:  
 * ===================================================================
 */
    void
display_sysinfo (Display *dpy, Window win, int scr, GC gc, 
                 unsigned int win_width, unsigned int win_height)
{

    XColor  Dark_Blue_col,              // 1
        Dark_Cyan_col,              // 2
        Dark_Goldenrod_col,         // 3
        Dark_GrayL_col,             // 4
        Dark_Green_col,             // 5
        Dark_Khaki_col,             // 6
        Dark_Magenta_col,           // 7
        Dark_Olive_Green_col,       // 8
        Dark_Orange_col,            // 9
        Dark_Orchid_col,            // 10
        Dark_Red_col,               // 11
        Dark_Salmon_col,            // 12
        Dark_Sea_Greenp_col,        // 13
        Dark_Slate_Blue_col,        // 14
        Dark_Slate_Gray_col,        // 15
        Dark_Turquoise_col,         // 16
        Dark_Violet_col,            // 17
        Deep_Pink_col,              // 18
        Deep_Sky_Blue_col,          // 19
        White_col,                  // 20
        Dark_Yellow_col,            // 21
        Light_Yellow_col,           // 22
        Black_col;                  // 23 To reset previously set the colours.


    Colormap            colormap;
    bool                uname_ok = false;
    struct utsname      sname;
    int                 ret = uname (&sname);
    char                buf[1024] = {0};
    int                 y_offset;
    const char          *s2 = "Developed by Onami Systems Ltd";
    int                 x_offset;
    
    char Dark_Blue[]=     "#00008B";  // 1 0% 0%  55% 240° 100% 27% 100% 55%
    char Dark_Cyan[]=     "#008B8B";  // 2 0%  55% 55% 180° 100% 27% 100% 55%
    char Dark_Goldenrod[]="#B8860B";  // 3 72% 53% 4%  43° 89% 38% 94% 72%
    char Dark_GrayL[]=    "#A9A9A9";  // 4 66% 66% 66% 0° 0% 66% 0% 66% 
    char Dark_Green[]=    "#006400";  // 5 0% 39% 0%  120° 100% 20% 100% 39%
    char Dark_Khaki[]=    "#BDB76B";  // 6 74% 72% 42% 56° 38% 58% 43% 74%
    char Dark_Magenta[]=  "#8B008B";  // 7 55% 0% 55% 300° 100% 27% 100%  55%
    char Dark_Olive_Green[]="#556B2F";// 8 33% 42% 18% 82° 39% 30% 56% 42%
    char Dark_Orange[]=    "#FF8C00"; // 9 100% 55% 0% 33° 100% 50% 100% 100%
    char Dark_Orchid[]=    "#9932CC"; // 10 60% 20% 80% 280°  61% 50% 75% 80%
    char Dark_Red[]=       "#8B0000"; // 11 55% 0%  0%  0°  100% 27% 100% 55%
    char Dark_Salmon[]=    "#E9967A"; // 12 91% 59% 48% 15° 72% 70% 48% 91%
    char Dark_Sea_Greenp[]= "#8FBC8F";// 13 56% 74% 56% 120° 25% 65% 24% 74%
    char Dark_Slate_Blue[]= "#483D8B";// 14 28% 24% 55% 248° 39% 39% 56% 55%
    char Dark_Slate_Gray[]= "#2F4F4F";// 15 18% 31% 31% 180°25% 25% 41% 31% 
    char Dark_Turquoise[]=  "#00CED1";// 16 0%  81% 82% 181° 100% 41%100% 82%
    char Dark_Violet[]=     "#9400D3";// 17 58% 0%  83% 282° 100% 41% 100% 83%
    char Deep_Pink[]=       "#FF1493";// 18 100% 8% 58% 328° 100% 54% 92% 100%
    char Deep_Sky_Blue[]=   "#00BFFF";// 19 0%75% 100% 195° 100% 50% 100% 100%

    char Black[]=          "#000000"; // 20 0% 0% 0% 0° 0% 0% 0% 0%
    char White[]=          "#FFFFFF"; // 21 100% 100% 100% 0° 0% 100% 0% 100%
    char Dark_Yellow[]=    "#FFCC00"; // 22 100% 80% 0% 48° 100% 50% 100% 100%
    char Light_Yellow[]=   "#FFFFE0"; // 23 100% 100% 88% 60° 100% 94% 12% 100%

    colormap = DefaultColormap (dpy, 0);
    
    XParseColor (dpy, colormap, Dark_Blue, &Dark_Blue_col);
    XAllocColor (dpy, colormap, &Dark_Blue_col);
    XParseColor (dpy, colormap, Dark_Cyan, &Dark_Cyan_col);
    XAllocColor (dpy, colormap, &Dark_Cyan_col);
    XParseColor (dpy, colormap, Dark_Goldenrod, &Dark_Goldenrod_col);
    XAllocColor (dpy, colormap, &Dark_Goldenrod_col);
    XParseColor (dpy, colormap, Dark_GrayL, &Dark_GrayL_col);
    XAllocColor (dpy, colormap, &Dark_GrayL_col);
    XParseColor (dpy, colormap, Dark_Green, &Dark_Green_col);
    XAllocColor (dpy, colormap, &Dark_Green_col);
    XParseColor (dpy, colormap, Dark_Khaki, &Dark_Khaki_col);
    XAllocColor (dpy, colormap, &Dark_Khaki_col);
    XParseColor (dpy, colormap, Dark_Magenta, &Dark_Magenta_col);
    XAllocColor (dpy, colormap, &Dark_Magenta_col);
    XParseColor (dpy, colormap, Dark_Olive_Green, &Dark_Olive_Green_col);
    XAllocColor (dpy, colormap, &Dark_Olive_Green_col);
    XParseColor (dpy, colormap, Dark_Orange, &Dark_Orange_col);
    XAllocColor (dpy, colormap, &Dark_Orange_col);
    XParseColor (dpy, colormap, Dark_Orchid, &Dark_Orchid_col);
    XAllocColor (dpy, colormap, &Dark_Orchid_col);
    XParseColor (dpy, colormap, Dark_Red, &Dark_Red_col);
    XAllocColor (dpy, colormap, &Dark_Red_col);
    XParseColor (dpy, colormap, Dark_Salmon, &Dark_Salmon_col);
    XAllocColor (dpy, colormap, &Dark_Salmon_col);
    XParseColor (dpy, colormap, Dark_Sea_Greenp, &Dark_Sea_Greenp_col);
    XAllocColor (dpy, colormap, &Dark_Sea_Greenp_col);
    XParseColor (dpy, colormap, Dark_Slate_Blue, &Dark_Slate_Blue_col);
    XAllocColor (dpy, colormap, &Dark_Slate_Blue_col);
    XParseColor (dpy, colormap, Dark_Slate_Gray, &Dark_Slate_Gray_col);
    XParseColor (dpy, colormap, Dark_Turquoise, &Dark_Turquoise_col);
    XAllocColor (dpy, colormap, &Dark_Turquoise_col);
    XParseColor (dpy, colormap, Dark_Violet, &Dark_Violet_col);
    XAllocColor (dpy, colormap, &Dark_Violet_col);
    XParseColor (dpy, colormap, Deep_Pink, &Deep_Pink_col);
    XAllocColor (dpy, colormap, &Deep_Pink_col);
    XParseColor (dpy, colormap, Deep_Sky_Blue, &Deep_Sky_Blue_col);
    XAllocColor (dpy, colormap, &Deep_Sky_Blue_col);
    XParseColor (dpy, colormap, Black, &Black_col);
    XAllocColor (dpy, colormap, &Black_col);
    XParseColor (dpy, colormap, White, &White_col);
    XAllocColor (dpy, colormap, &White_col);
    XParseColor (dpy, colormap, Dark_Yellow, &Dark_Yellow_col);
    XAllocColor (dpy, colormap, &Dark_Yellow_col);
    XParseColor (dpy, colormap, Light_Yellow, &Light_Yellow_col);
    XAllocColor (dpy, colormap, &Light_Yellow_col);

    if (ret != -1) {
        uname_ok = true;
    }
#if defined (__APPLE_CC__)
    XStoreName (dpy, win,"X11 window under Mac OS X (Lion)");
    const char *s1 = "X11 test app under the Mac IS X Lion";
#else
    XStoreName (dpy, win, "X11 window under Linux OS");
    const char *s1 = "X11 Org app under Linux OS";
#endif
      x_offset = 0;        //win_width / 4 - width / 2;
      y_offset = 140;

      XDrawString(dpy, win, gc, x_offset, y_offset,(char*)s1, strlen(s1));
      y_offset += 20;
      XDrawString(dpy, win, gc, x_offset, y_offset,(char*)s2, strlen(s2));
      y_offset += 20;

      if (uname_ok)
      { get_spen (dpy, gc, Dark_Yellow_col);
        sprintf(buf, "System information:");
        XDrawString(dpy, win, gc, x_offset, 
                    y_offset, (char*)buf, strlen(buf));
        get_spen (dpy, gc, White_col);
        y_offset += 20;

        get_spen (dpy, gc, Dark_Goldenrod_col);
        sprintf(buf, "- System: %s", sname.sysname);
        XDrawString(dpy, win, gc, x_offset, 
                    y_offset, (char*)buf, strlen(buf));
        get_spen (dpy, gc, White_col);
        y_offset += 20;
        get_spen (dpy, gc, Light_Yellow_col);
        sprintf(buf, "- Release: %s", sname.release);
        XDrawString(dpy, win, gc, x_offset, 
                    y_offset, (char*)buf, strlen(buf));
        get_spen (dpy, gc, White_col);
        y_offset += 20;
        get_spen (dpy, gc, Dark_Orange_col);
        sprintf(buf, "- Version: %s", sname.version);
        XDrawString(dpy, win, gc, x_offset, 
                    y_offset, (char*)buf, strlen(buf));
        get_spen (dpy, gc, White_col);
        y_offset += 20;

        sprintf(buf, "- Machine: %s", sname.machine);
        XDrawString(dpy, win, gc, x_offset, 
                    y_offset, (char*)buf, strlen(buf));
        y_offset += 20;
        
        get_spen (dpy, gc, Dark_Cyan_col);

        get_ip_address ();

        sprintf (buf, "- IP Address: %s", ipa);         
        XDrawString (dpy, win, gc, x_offset,
                    y_offset, (char*)buf, strlen (buf));

        get_spen (dpy, gc, White_col);
        y_offset += 20;

        get_mac_address ();

        get_spen (dpy, gc, Dark_Orange_col);
        sprintf (buf, "- MAC Address:   ");         
        XDrawString (dpy, win, gc, x_offset,
                    y_offset, (char*)buf, strlen (buf));

        get_spen (dpy, gc, White_col);
        XDrawString (dpy, win, gc, x_offset + 130,
                    y_offset, (char*)mac, strlen (mac));

        get_spen (dpy, gc, White_col);
        y_offset += 20;

        get_hostname ();

        get_spen (dpy, gc, Deep_Pink_col);
        sprintf (buf, "- Host Name: %s", hst );          
        XDrawString (dpy, win, gc, x_offset,
                    y_offset, (char*)buf, strlen (buf));
        y_offset += 20;
        get_spen (dpy, gc, White_col);

        const char *env_var[MAX_VAL] = {
                                "COLORTERM",
                                "HOME",
                                "LANGUAGE",
                                "DESKTOP_SESSION",
                                "LOGNAME",
                                "XDG_SESSION_TYPE",
                                "SYSTEMD_EXEC_PID",
                                "XAUTHORITY",
                                "J2REDIR",
                                "USERNAME",
                                "LANG",
                                "XDG_CURRENT_DESKTOP",
                                "XDG_SESSION_CLASS",
                                "TERM",
                                "LC_ALL",
                                "XDG_RUNTIME_DIR",
                                "XDG_CONFIG_DIRS",
                                "HISTCONTROL",
                                "HISTTIMEFORMAT",
                                "GTK_MODULES",
                                "SYSTEMD_EXEC_PID",
                                "SSH_AGENT_LAUNCHER",
                                "HISTCONTROL",
                                "SESSION_MANAGER",
                                "SHELL",
                                "DERBY_HOME",
                                "JAVA_HOME",
                                "LD_LIBRARY_PATH",
                                "PATH",
                                "PWD",
                                "DISPLAY"
                             };
    char *env_val[MAX_VAL];

    srand (time (NULL));    // random numbers

    for (int i=0; i<MAX_VAL; i++) {
        /* Getting enviroment value if exists */
        env_val[i] = getenv (env_var[i]);
        if (env_val[i] != NULL) {
           sprintf (buf, "- %s: %s\n", env_var[i], env_val[i]);

           get_spen (dpy, gc, Dark_Yellow_col);
           XDrawString (dpy, win, gc, x_offset,
                   y_offset, (char*)buf, strlen (buf));
           y_offset += 20;
           buf[0] = '\0';
        } else {
            printf ("%s : does't exists\n", env_var[i]);
            }
        }
   }
   get_spen (dpy, gc, White_col);
}		/* -----  end of function display_sysinfo  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  bool loadFont (char *fontname)
 *  Description:  
 * ===================================================================
 */
Bool loadFont (char *fontname, FontCache fnt[], Display *dpy, GC gc, int cf)
{
    int i, next_i;

    for (i=0; i<NUM_FONTS; ++i)
    {   
       if (strcmp (fontname, fnt[i].name) == 0) break;
    } 

    if (i == NUM_FONTS)
    {
        i = next_i=0;
        XUnloadFont (dpy, fnt[i].f);
        free (fnt[i].name);
        fnt[i].name = NULL;
        next_i = (next_i +1) % NUM_FONTS;
    }
    if (!fnt[i].name)
    {
        fnt[i].f = XLoadFont (dpy, fontname);
        fnt[i].name = strdup (fontname);
    }
    XSetFont (dpy, gc, fnt[i].f);
    cf = i;
    return (True);
}		/* -----  end of function bool loadFont (char *fontname)  ----- */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int LoadImage
 *  Description:  
 * ===================================================================
 */
int LoadImage (char *fname, Display *dpy, Window win, int scrn)
{
    int i; 
    int ret; 
    char *err = NULL; 
    char *actname;
    
    for (i=0; i< MAX_IMAGES; ++i) {
         if (!Images[i].used) {
             memset (&Images[i], 0, sizeof (Images[i]));     
            Images[i].xAtt.closeness = 40000;
            Images[i].xAtt.valuemask = XpmCloseness;
         }
    }
    actname = FindXPMFile (fname);

    if (actname == NULL)
        err =(char*) "No such file exists!";
    else {
        ret = XpmReadFileToPixmap (dpy, win, actname,
                                   &Images[i].pixmap,
                                   &Images[i].clipmask,
                                   &Images[i].xAtt);
      switch (ret)
      {
        case XpmColorError:
            err = (char*)"Could not parse or alloc requested color";
            break;
        case XpmOpenFailed:
            err = (char*)"Cannot open file";
            break;
        case XpmFileInvalid:
            err = (char*)"Invalid XPM file";
            break;
        case XpmNoMemory:
            err = (char*)"Not enough memory";
            break;
        case XpmColorFailed:
            err = (char*)"Failed to parse or alloc some color";
            break;
       }
    }
    if (err) {
        fprintf (stderr, "%s:", fname);
        printf (" %s\n", err);
        exit (-1);
    }
    Images[i].saved = XCreatePixmap (dpy, win,
                                     Images[i].xAtt.width,
                                     Images[i].xAtt.height,
                                     DefaultDepth (dpy, scrn));
    Images[i].used = 1;
    return i;
}		/* -----  end of function int LoadImage  ----- */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  char *FindXPMFile (char *fname)
 *  Description:  Return pointer to static name of apparently existing XPM 
 *                file. As well as trying to append ".xpm", we try 
 *                prepending the value of the environment variable 
 *                XPMDIR if it exists.
 * ===================================================================
 */
char *FindXPMFile (char *fname)
{
 /*   static char name[256] = {0};
    char *xpmdir, *getenv();
    struct stat buf;
    char *ptr;

    sprintf (name, "%s", fname);
    if (stat (name, &buf) == 0) {return ptr = name; }

    sprintf (name, "%s.xpm", fname);
    if (stat (name, &buf) == 0) {return ptr = name; }

    if (fname[0] == '/' || (xpmdir = getenv("XPMDIR")) == NULL)
        return NULL;

    sprintf (name, "%s/%s", xpmdir, fname);
    if (stat (name, &buf) == 0) { return ptr = name; }
    sprintf (name, "%s/%s.xpm", xpmdir, fname);
    if (stat (name, &buf) == 0) { return ptr = name; }
*/    
    return NULL;
}		/* -----  end of function char *FindXPMFile (char *fname)  ----- */

